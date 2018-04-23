/*
 * Arcomage Tribute
 *
 * File: singleton.h
 * Desc: Singleton Template
 *
 * Date: 07/2007
 *
 * Copyright (C) 2006,2007 Xography. <www.gatewayheaven.com>
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

namespace arcomage {
	template <typename ASingleton>
	class Singleton {
	public:
		static ASingleton* getInstance()
		{
			if (!_instance)
				_instance = new ASingleton();
			return _instance;
		}
		virtual        ~Singleton()
		{
			_instance = 0;
		}
	private:
		static ASingleton* _instance;
	protected:
		Singleton()
		{
		}
	};
	template <typename ASingleton>
	ASingleton* Singleton<ASingleton>::_instance = 0;
}
#endif // SINGLETON_H_INCLUDED
