/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Runs a command as root, similar to sudo, without asking for a password.
   Do not give this binary setuid/root ownership unless for hacking purposes! */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  if (argc > 1)
    {
      pid_t pid = fork ();
      if (pid < 0)
	{
	  fprintf (stderr, "fake-sudo: couldn't fork\n");
	  exit (1);
	}
      else if (pid == 0)
	{
	  argv++;
	  if (setuid (0) == -1)
	    {
	      fprintf (stderr, "fake-sudo: couldn't setuid: %s\n",
		       strerror (errno));
	      exit (1);
	    }
	  if (setgid (0) == -1 && errno == EPERM)
	    {
	      fprintf (stderr, "fake-sudo: couldn't setgid: %s\n",
		       strerror (errno));
	      exit (1);
	    }
	  execvp (*argv, argv);
	  exit (2);
	}
      else
	{
	  int status;
	  waitpid (pid, &status, 0);
	}
    }
  else
    fprintf (stderr, "usage: fake-sudo COMMAND [ARGS...]\n");
  return 0;
}
