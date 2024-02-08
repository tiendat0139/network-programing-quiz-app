#ifndef __TYPE_H__
#define __TYPE_H__

/* Message type  */
#define REQUEST_GET_RESOURCE "0x00"
#define RESPONSE_GET_RESOURCE "0x01"
#define REQUEST_CREATE_RESOURCE "0x02"
#define RESPONSE_CREATE_RESOURCE "0x03"
#define REQUEST_EDIT_RESOURCE "0x04"
#define RESPONSE_EDIT_RESOURCE "0x05"
#define REQUEST_DELETE_RESOURCE "0x06"
#define RESPONSE_DELETE_RESOURCE "0x07"

/* Status type */
#define SUCCESS "SUCCESS"
#define FAILURE "FAILURE"
#define ERROR "ERROR"

/* Room type */
#define ROOM_EXAM_TYPE "exam"
#define ROOM_PRACTICE_TYPE "practice"

/* Room status */
#define ROOM_LOBBY_STATUS "Lobby"
#define ROOM_DOING_STATUS "Doing"
#define ROOM_CLOSE_STATUS "Close"

#endif
