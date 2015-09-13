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
#include "pch.h"
#pragma once
#include "Version.h"
#include "Config.h"

namespace librevault {

class Exchanger;
class Session {
public:
	Session(const po::variables_map& vm);
	virtual ~Session();

	void init_log();

	void run();
	void run_worker(unsigned worker_number);
	void shutdown();
	void restart();

	Exchanger& exchanger(){return *exchanger_;}

	const Version& version() const {return version_;}
	logger_ptr log() {return log_;}
	io_service& ios(){return io_service_;}
	ptree& config(){return config_->config();}

	fs::path appdata_path() const {return appdata_path_;}
	fs::path config_path() const {return config_path_;}
	fs::path log_path() const {return log_path_;}
	fs::path key_path() const {return key_path_;}
	fs::path cert_path() const {return cert_path_;}
private:
	Version version_;	// Application name and version information (probably, it will contain application path and signature later)
	io_service io_service_;	// Asynchronous/multithreaded operation
	logger_ptr log_;	// Logging
	std::unique_ptr<Config> config_;	// Configuration

	// Components
	std::unique_ptr<Exchanger> exchanger_;

	// Paths
	fs::path default_appdata_path();
	fs::path appdata_path_, config_path_, log_path_, key_path_, cert_path_;
};

} /* namespace librevault */
