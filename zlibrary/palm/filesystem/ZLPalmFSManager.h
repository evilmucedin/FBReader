/*
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

#ifndef __ZLPALMFSMANAGER_H__
#define __ZLPALMFSMANAGER_H__

#include <abstract/ZLFSManager.h>

class ZLPalmFSManager : public ZLFSManager {

public:
	static void createInstance() FS_SECTION;
	~ZLPalmFSManager() FS_SECTION;
	
private:
	ZLPalmFSManager() FS_SECTION;
	
public:
	void normalize(std::string &fileName) FS_SECTION;
	ZLFSDir *createDirectory(const std::string &name) FS_SECTION;
	ZLInputStream *createInputStream(const std::string &name) FS_SECTION;
	ZLOutputStream *createOutputStream(const std::string &name) FS_SECTION;
};

#endif /* __ZLPALMFSMANAGER_H__ */
