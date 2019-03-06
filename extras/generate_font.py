#!/usr/bin/env python

# This file is part of the MKRRGBMatrix library.
# Copyright (c) 2018 Arduino SA. All rights reserved.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

import sys;

input = sys.argv[1]
output = sys.argv[2]
name = sys.argv[3]

fontWidth = 0
fontHeight = 0
fontCharacters = [None] * 256
fontCharacterNames = [None] * 256

with open(input) as f:
	charName = ""
	charEncoding = -1
	charBitmap = []

	bitmap = False

	for line in f:
		line = line.rstrip();
		splitLine= line.split(" ")

		if splitLine[0] == "FONTBOUNDINGBOX":
			fontWidth = int(splitLine[1])
			fontHeight = int(splitLine[2])
		elif splitLine[0] == "STARTCHAR":
			charName = splitLine[1];
		elif splitLine[0] == "ENCODING":
			charEncoding = int(splitLine[1])
		elif splitLine[0] == "BITMAP":
			bitmap = True
			charBitmap = []
		elif splitLine[0] == "ENDCHAR":
			if charEncoding <= 255:
				fontCharacterNames[charEncoding] = charName
				fontCharacters[charEncoding] = charBitmap
			charEncoding = -1
			bitmap = False
		elif bitmap:
			charBitmap.append(int(line, 16))

out = open(output, "w")

print >> out, "#include \"Font.h\""
print >> out
print >> out, "const struct Font %s = {" % ( name )
print >> out, "  %d," % ( fontWidth )
print >> out, "  %d," % ( fontHeight )
print >> out, "  (const uint8_t*[]){"
for c in range (0, 255):
	if None == fontCharacters[c]:
		print >> out, "    NULL,"
	else:
		print >> out, "    // %s" % (fontCharacterNames[c])
		print >> out, "    (const uint8_t[]){"
		for i in range(0, fontHeight):
			print >> out, "      0b%s," % ('{0:08b}'.format(fontCharacters[c][i]))
		print >> out, "    },"
print >> out, "  }"
print >> out, "};"

out.close()
