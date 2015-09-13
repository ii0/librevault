/* Copyright (C) 2015 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../pch.h"
#pragma once

namespace librevault {

class Session;

class FSDirectory;
class P2PProvider;

class Exchanger {
public:
	Exchanger(Session& session);
	virtual ~Exchanger();

	void register_directory(std::shared_ptr<FSDirectory> dir_ptr);
	void unregister_directory(std::shared_ptr<FSDirectory> dir_ptr);

	std::shared_ptr<FSDirectory> get_directory(const fs::path& path);
	std::shared_ptr<FSDirectory> get_directory(const blob& hash);
private:
	Session& session_;
	std::shared_ptr<spdlog::logger> log_;

	// Remote
	std::unique_ptr<P2PProvider> p2p_provider_;

	std::map<fs::path, std::shared_ptr<FSDirectory>> path_dir_;
	std::map<blob, std::shared_ptr<FSDirectory>> hash_dir_;

	void add_directory(const ptree& dir_options);
};

} /* namespace librevault */
