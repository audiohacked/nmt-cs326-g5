IF(${CHAT_ENABLED} MATCHES ON)
INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	chat/gloox/src
)
ADD_SUBDIRECTORY(chat/gloox)
SET(DDPS_LIBS ${DDPS_LIBS} gloox)
ENDIF(${CHAT_ENABLED} MATCHES ON)