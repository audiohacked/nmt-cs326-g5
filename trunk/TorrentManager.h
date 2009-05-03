#ifndef __TORRENT_MANAGER_H
#define __TORRENT_MANAGER_H

	#include <libtorrent/session.hpp>
	#include "TorrentAlertTimer.h"

	/*
		construct a session
		parse torrent files and add to session; or add torrent hashs to session
		main loop:
			query the torrent_handles for progress (see torrent_handle)
			query the session for information
			add and remove torrents from the session at run-time
		save resume data
		destruct session object

	*/
	class DDPSConfig;
	class TorrentTransferManager
	{
		public:
			libtorrent::session se;
			libtorrent::session_settings settings;
			libtorrent::session_status status;
			download_handles_t *handles;
			TorrentAlertTimer *alert_timer;
			DDPSConfig *torrent_cfg;
			TorrentTransferManager(download_handles_t *l);
			~TorrentTransferManager();

			libtorrent::torrent_handle AddMagnetURI(char const* uri, long index);
			libtorrent::torrent_handle AddTorrentFile(char const* file, long index);
			libtorrent::torrent_handle AddTorrentHash(char const* name, 
				char const* tracker, libtorrent::sha1_hash const& hash, long index);

			bool startTransfer();
			bool cancelTransfer();
			bool pauseTransfer();
			bool finishTransfer();
			bool connectToPeers();
			bool downloadTorrent();
			bool uploadTorrent();
			bool setTransferSpeed();
			int getSessionStatus();
			
			libtorrent::dht_settings dht_settings;
			libtorrent::entry dht_state;
	};
	
/*	class TorrentTransfer : public TorrentTransferManager, public entry
	{
		public:
			int transferID;
			int progress;
			torrent_info torrentInfo;
			torrent_handle torrentHandle;
			//File fileList;
						
			TorrentTransfer(big_number const& hash);
			~TorrentTransfer();
			
			int getTransferAttributes();
			int getTransferProgress();			
			bool verifyFiles();
	}; */

#endif
