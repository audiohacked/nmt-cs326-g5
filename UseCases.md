# List of Actors #
List probable actors below:
  * Basic User (human)
  * Content Distributor/Server Admin (human, inherits from user)
  * Database
  * Centralized Content Server
  * Tracker (for torrents)

# Use Case Diagram #

When we're satisfied with the use cases below we can convert them into a big use case diagram here.
## Second Version ##
![http://nmt-cs326-g5.googlecode.com/files/usecasev2_2.jpeg](http://nmt-cs326-g5.googlecode.com/files/usecasev2_2.jpeg)
## First Version ##
![http://nmt-cs326-g5.googlecode.com/files/usecase.jpeg](http://nmt-cs326-g5.googlecode.com/files/usecase.jpeg)
I really tried to minimize criss-crossing the lines and came up with this.  I color coded the <

&lt;include&gt;

>, <

&lt;extends&gt;

, and inheritance relationships.

# Use Case Diagram by Actors #
## Basic User ##
![http://nmt-cs326-g5.googlecode.com/files/UseCase_BasicUser.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_BasicUser.jpeg)
## Content Distributor ##
![http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentDistributor.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentDistributor.jpeg)
## Tracker ##
![http://nmt-cs326-g5.googlecode.com/files/UseCase_Tracker.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_Tracker.jpeg)
## Centralized Content Server ##
![http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentServer.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_ContentServer.jpeg)
## Database ##
![http://nmt-cs326-g5.googlecode.com/files/UseCase_Database.jpeg](http://nmt-cs326-g5.googlecode.com/files/UseCase_Database.jpeg)

# Use Case Details #
Below is a table containing every use case along with auxiliary information.

| _Use Case_ | _Actor(s)_ | _Entry Condition_ | _Exit Condition_  | _Extends/Includes/Inherits_ |
|:-----------|:-----------|:------------------|:------------------|:----------------------------|
| DownloadFile | Basic User | User initiates a file download from the content server (can be an actual file or a torrent file). | User finishes file download or file download error. | **Includes** ReportTransferProgress, ReportFileDownload |
| DownloadHTTPFile | Basic User, Centralized Content Server | User downloads a file from content server over HTTP. | File transfer completes or file transfer error. | **Inherits** DownloadFile |
| DownloadTorrentFile | Basic User, Tracker | User initiates a file download via BitTorrent. | User completes download and shares file to a specified ratio, or user opts to stop sharing or downloading the file prematurely. | **Inherits** DownloadFile |
| ReportFileDownload | Database | A file transfer to the client completes. | File download statistics are reported and stored in the database. | N/A |
| ReportFileUpload | Database | File finishes uploading to the Centralized Content Server. | The database has allocated the proper space and structure to accommodate statistics for the sponsored file. | N/A |
| UploadFile | Basic User, Centralized Content Server  | User selects a file which will become sponsored content. | File is uploaded to centralized content server. | **Includes** ReportFileUpload, ReportTransferProgress, DesignateFileSponsoredStatus |
| DesignateFileSponsoredStatus | Content Distributor, Database | Content distributor designates a file which he/she wants to have/lose sponsored status. | File's database entry is updated to reflect desired sponsored status. | N/A |
| GetFileStatistics | Basic User, Database | User selects a file for which usage statistics are desired. | Database completes reporting relevant information about desired file to client. | N/A |
| ReportTransferProgress | Basic User | User begins a file transfer. | File transfer completes. | N/A |
| BrowseContentSite | Basic User, Centralized Content Server | User requests a page/navigates in the centralized content server's website. | Content Server serves the client the desired page. | N/A |
| RemoveFile | Basic User, Centralized Content Server, Database | User/Distributor selects a file to be removed from the distribution system. | The server has deleted the file, the database has removed/archived information about the file. | N/A |
| SetClientPreferences | Basic User | User opens Preferences dialog. | User's preferences are committed to a configuration file. | N/A |
| SetServerPreferences | Content Distributor, Centralized Content Server | User opens Server Preferences dialog (could be in website with credentials). | New preferences are committed to server configuration file. | N/A |
| AbortFileTransfer | Basic User | User opts to cancel a file transfer or an error occurs. | File transfer is stopped and any intermediate data is disposed of. | N/A |
| ExTransferError | Basic User _and/or_ Centralized Content Server | Error occurs during a file transfer. | Error is resolved and/or reported to the user. | **Includes** AbortFileTransfer, **Extends** DownloadFile, UploadFile |
| ExFileNotFoundError | Centralized Content Server | Server cannot locate requested file. | Server logs the error and aborts the transfer. | **Inherits** ExTransferError |
| ExHTTPTransferError | Basic User _and/or_ Centralized Content Server | An error occurs during an HTTP file transfer. | Error is resolved and/or reported to the user.  If the file was a sponsored file, error is reported to the content server. | **Inherits** ExTransferError, **Extends** DownloadHTTPFile |
| ExTorrentTransferError | Basic User, Tracker | An error occurs during a BitTorrent file transfer.  | Error is resolved and/or reported to the user and the tracker. | **Inherits** ExTransferError, **Extends** DownloadTorrentFile |

# Flow of Events #
See each use case for its flow of events.