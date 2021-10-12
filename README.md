# head

This is a clone of the head system program command, but it only works for one file.
Here is the man file for it that has been modified to show that it only works for one input file.

---
**HEAD**

**NAME**
     **head** -- display first lines of a file

**SYNOPSIS**
     **head** [**-n** __count__ | **-c** __bytes__] [file]

**DESCRIPTION**
     This filter displays the first __count__ lines or __bytes__ of each of the speci-
     fied files, or of the standard input if no files are specified.  If __count__
     is omitted it defaults to 10.

**EXIT STATUS**
     The **head** utility exits 0 on success, and >0 if an error occurs.
(END)
