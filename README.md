keep-the-best
=============

A simple dedup

###NAME###
   ktb - prints on stdout a bash script for removing duplicate files.

###SYNOPSIS###
   ktb < hashes.txt folder

###DESCRIPTION###
   hashes.txt is the output of an md5deep command
   
   folder     is the folder where to move the duplicate files

###EXAMPLE###
   The bash script dedup.sh moves all the duplicates found in /home/alex/pdf
   (and all its subdir) to /home/alex/dup/

   md5deep /home/alex/pdf -r | ktb /home/alex/dup/ > dedup.sh

###AUTHOR###
   Alessandro Gentilini, January 2014.
   
   https://github.com/alessandro-gentilini/keep-the-best
   

To install `md5deep`
====================
`sudo apt-get install md5deep`


