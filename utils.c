#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))

char* getRandomEnding();

void expressFrustration(char* msg) {
	printf("Oh my gosh! I can't do that!! ");
	printf(msg);
	printf(". ");
	printf(getRandomEnding());
	printf("\n");
	exit(0);
}

char* getRandomEnding() {
	char* endings[] = {"Sheesh.", "How is that not obvious to you!?", "Seriously.", "What's your problem?", "l2 server!", "noob.", "I seriously cannot handle much more of this.", "Idiot.", "Your inability to use this exe disturbs me.", "It's not hard, man.", "I seriously can't believe how much crap I put up with.", "I am such a martyr.", "Sorry, It's just been a long day, and I've never been good at managing my anger. I'm working on it, though", "Good luck with life.", "Yo dawg, I heard you like fail, so I put some fail in your fail so you can fail while you fail!!"};
	int length = ARRAY_SIZE(endings);
	int index = rand() % 15;
	return endings[index];
}
