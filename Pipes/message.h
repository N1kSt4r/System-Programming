#pragma once

struct Message {
	char sender[10];
	char receiver[10];
	char text[20];
};

typedef struct Message Message;