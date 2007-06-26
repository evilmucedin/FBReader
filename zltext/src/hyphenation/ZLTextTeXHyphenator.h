/*
 * Copyright (C) 2004-2007 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __TEXHYPHENATOR_H__
#define __TEXHYPHENATOR_H__

#include <vector>
#include <string>

#include "ZLTextHyphenator.h"

class ZLTextTeXHyphenationPattern {

public:
	ZLTextTeXHyphenationPattern(unsigned short *ucs2String, int length);
	ZLTextTeXHyphenationPattern(const std::string &utf8String);
	~ZLTextTeXHyphenationPattern();

	int length() const { return myLength; }
	void apply(unsigned char *values) const;

private:
	int myLength;
	unsigned short *mySymbols;
	unsigned char *myValues;

friend class ZLTextTeXPatternComparator;
};

class ZLTextTeXPatternComparator {

public:
	bool operator() (const ZLTextTeXHyphenationPattern *p1, const ZLTextTeXHyphenationPattern *p2) const;
};

class ZLTextTeXHyphenator : public ZLTextHyphenator {

private:
	static const std::string PatternZip();
	static std::vector<std::string> LanguageCodes;
	static std::vector<std::string> LanguageNames;
	static void collectLanguages();

public:
	static const std::vector<std::string> &languageCodes();
	static const std::vector<std::string> &languageNames();

public:
	ZLTextTeXHyphenator() : myBreakingAlgorithm("") {}
	~ZLTextTeXHyphenator();

	void load(const std::string &language);
	void unload();

	const std::string &breakingAlgorithm() const;

protected:
	void hyphenate(std::vector<unsigned short> &ucs2String, std::vector<unsigned char> &mask, int length) const;

private:
	typedef std::vector<ZLTextTeXHyphenationPattern*>::const_iterator PatternIterator;

	std::vector<ZLTextTeXHyphenationPattern*> myPatternTable;
	std::string myLanguage;

	std::string myBreakingAlgorithm;

friend class ZLTextHyphenationReader;
};

#endif /* __TEXHYPHENATOR_H__ */