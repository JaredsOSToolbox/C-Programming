# Stripping grep from ed

Princeton assignment to obtain the regular expression library from the text editor `ed`.
The original assignment required it to be under 400 lines of code, however, I am going to use `clang-format` to make it readable.

## Building

Please use the `grep_testing` script to build.
If you're using a different shell interpreter other than `zsh`, please make the necessary changes to use this script.

```bash
# run the tests
./grep_testing
```

## REGEX testing

- Find and replace all instances: `,s/line/replaced/g`
- Find and replace all instances where `line` is the first expression: `,s/^line/replaced/g`

This project is meant to strip the grep regex engine out of ed.
Since all we need is a text processor, the approach is sort of straight forward.....
Firstly, we need to identify what is the heart of the grep component.

These functions stand out the most:

- compile
- execute
- backref
- cclass


Now, we need to figure out how on Earth they work and tinker with a regular expression engine works.

## compile

Defined macros and their meanings:

- CCIRC: "^" symbol is ingested and this regex symbol denotes the beginning of a line. We want to peek forward to see the value after the carat. For example, "^Hello" will match "Hello World" but not "World, Hello" and the value of peek char would be "H".
- CEOF: signals that we are at the end of the file. We only need this for reading from STDIN.

I would like to mention that I attempted to document how it works but quickly gave up due to the sheer volume of code that needed to be sifted through.
Some of this I understand to a slight degree but a lot of this code I have absolutely **NO IDEA** how it works.
I kept deleting functions and tested if the program still functioned as intended.
For further development of this project, it would be advised to revert several one liners into multiple lines, **as the current state of affairs is unreadable**.

# External Links

- [ED Regular Expression Syntax Documentation](https://www.gnu.org/software/gnulib/manual/html_node/ed-regular-expression-syntax.html)
- [GNU 'ed' Manual](https://www.gnu.org/software/ed/manual/ed_manual.html)
- [Using 'ed' YouTube video](https://www.youtube.com/watch?v=UQOHNT36ioQ)
- [Computer Hope Article on 'ed'](https://www.computerhope.com/unix/ued.htm)
- [Linux Die Manual Page](https://linux.die.net/man/1/ed)

# Using git

- [How can I restore a previous version of my project](https://www.git-tower.com/learn/git/faq/restore-repo-to-previous-revision)
- [Git commit history](https://git-scm.com/book/en/v2/Git-Basics-Viewing-the-Commit-History)
