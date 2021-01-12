#pragma once

typedef enum { STATUS_START, STATUS_LEVEL, STATUS_END } status_t;

struct Disk {
	float cx, cy;
	float radius;
};