/*
 * FBReader -- electronic book reader
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <abstract/ZLOptionsDialog.h>

#include "StyleOptionsPage.h"

#include "../view/PaintContext.h"
#include "../textview/TextView.h"
#include "../textview/TextStyle.h"
#include "../textview/TextStyleOptions.h"

StyleOptionsPage::StyleOptionsPage(ZLOptionsDialogTab *dialogTab, PaintContext &context) {
	myComboEntry = new ComboOptionEntry(*this, "Options For", "Base");
	myComboEntry->addValue(myComboEntry->initialValue());

	TextStyleCollection &collection = TextStyleCollection::instance();
	const int STYLES_NUMBER = 19;
	TextKind styles[STYLES_NUMBER] = { REGULAR, TITLE, SECTION_TITLE, SUBTITLE, CONTENTS_TABLE_ENTRY, LIBRARY_AUTHOR_ENTRY, LIBRARY_BOOK_ENTRY, ANNOTATION, EPIGRAPH, AUTHOR, DATE, POEM_TITLE, STANZA, VERSE, CITE, FOOTNOTE, EMPHASIS, STRONG, CODE };
	for (int i = 0; i < STYLES_NUMBER; i++) {
		const TextStyleDecoration *decoration = collection.decoration(styles[i]);
		if (decoration != 0) {
			myComboEntry->addValue(decoration->name());
		}
	}
	dialogTab->addOption(myComboEntry);

	{
		const std::string &name = myComboEntry->initialValue();
		BaseTextStyle &baseStyle = collection.baseStyle();

		registerEntries(dialogTab,
			new FontFamilyOptionEntry(baseStyle.fontFamilyOption(), context, false),
			new ZLSimpleBooleanOptionEntry("Bold", baseStyle.boldOption()),
			name
		);

		registerEntries(dialogTab,
			new ZLSimpleSpinOptionEntry("Size", baseStyle.fontSizeOption(), 10, 32, 2),
			new ZLSimpleBooleanOptionEntry("Italic", baseStyle.italicOption()),
			name
		);

		registerEntry(dialogTab,
			new ZLSimpleBooleanOptionEntry("Auto Hyphenations", TextView::AutoHyphenationOption),
			name
		);
	}

	for (int i = 0; i < STYLES_NUMBER; i++) {
		const TextStyleDecoration *decoration = collection.decoration(styles[i]);
		if (decoration != 0) {
			const std::string &name = decoration->name();

			registerEntries(dialogTab,
				new FontFamilyOptionEntry(decoration->fontFamilyOption(), context, true),
				new ZLSimpleBoolean3OptionEntry("Bold", decoration->boldOption()),
				name
			);

			registerEntries(dialogTab,
				new ZLSimpleSpinOptionEntry("Size Difference", decoration->fontSizeDeltaOption(), -16, 16, 2),
				new ZLSimpleBoolean3OptionEntry("Italic", decoration->italicOption()),
				name
			);

			registerEntry(dialogTab,
				new ZLSimpleBooleanOptionEntry("Allow Hyphenations", decoration->allowHyphenationsOption()),
				name
			);
		}
	}

	myComboEntry->onValueChange(myComboEntry->initialValue());
}
