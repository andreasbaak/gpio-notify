/**
 * Copyright 2015 Andreas Baak (andreas.baak@gmail.com)
 * License: GPLv2
 */

#include <cstdlib>
#include <glib.h>
#include <iostream>
#include <fcntl.h>

const int bufer_size = 1024;
gchar read_buffer[bufer_size] = {};

GIOStatus g_io_read_buffer(GIOChannel *channel)
{
  GError* error = 0;
  gsize bytes_read = 0;
  g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
  GIOStatus rc = G_IO_STATUS_AGAIN;
  while (rc == G_IO_STATUS_AGAIN)
  {
    rc = g_io_channel_read_chars( channel, read_buffer, bufer_size - 1, &bytes_read, &error );
    if (rc == G_IO_STATUS_ERROR)
    {
      std::cerr << "Could not read channel: " << error->message << std::endl;
    }
  }
  return rc;
}

gboolean onFileChangedEvent(GIOChannel *channel, GIOCondition, gpointer filename)
{
  GIOStatus rc = g_io_read_buffer(channel);
  if (rc != G_IO_STATUS_NORMAL)
  {
    exit(1);
  }
  else
  {
    std::cout << (const char*) filename << " " << read_buffer;
    exit(0);
  }
  return false;
}

void usage(const char* prog_name)
{
  std::cout << "Usage:" << std::endl;
  std::cout << prog_name << " <gpio_value_filename0> <gpio_value_filename1> ..." << std::endl;
  std::cout << std::endl;
  std::cout << "Example:" << std::endl;
  std::cout << "  gpio-notify /sys/class/gpio/gpio20/value" << std::endl;
  std::cout << std::endl;
  std::cout << "Note that the following settings have to be enabled for the gpio port: " << std::endl;
  std::cout << "  echo in > direction" << std::endl;
  std::cout << "  echo both > edge" << std::endl;
  std::cout << std::endl;
  std::cout << "Wait for any of the provided gpio value files to change." << std::endl;
  std::cout << "If the content of any of the files changed, " << std::endl;
  std::cout << "the name of the changed file and its contents" << std::endl;
  std::cout << "are written to stdout, for example:" << std::endl;
  std::cout << "/sys/class/gpio/gpio60/value 1" << std::endl;
  exit(1);
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    usage(argv[0]);
  }

  GMainLoop* loop = g_main_loop_new(0, 0);
  for (int i = 1; i < argc; ++i)
  {
    const char* filename = argv[i];
    const int fd = open(filename, O_RDONLY | O_NONBLOCK);
    GIOChannel* channel = g_io_channel_unix_new(fd);
    // Throw away the first reading in order not to fire the event immediately
    g_io_read_buffer(channel);
    GIOCondition cond = GIOCondition(G_IO_PRI);
    g_io_add_watch(channel, cond, onFileChangedEvent, (gpointer)filename);
  }
  g_main_loop_run(loop);
}

