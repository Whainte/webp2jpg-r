# webp2jpg-r
A tool for converting webp images into jpg format

this program converts ALL .webp files in the current folder AND IT'S ALL SUBFOLDERS into .jpg format.
the current version does NOT detect .webp files that are not webp images. be causious.
the program doesnt receive any parameters from the shell and is currently for webp->jpg only.

This program includes ImageMagick, by ImageMagick Studio LLC
    which doesnt generate a proper functional executable on debug.
	Image Magick is released under Apache License 2.0
	https://www.imagemagick.org/script/license.php
This program uses \<filesystem\> from C++14 and is tested on x64 only.(VS2017 Community)
