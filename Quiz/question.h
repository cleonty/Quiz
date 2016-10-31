#ifndef QUESTION_H
#define QUESTION_H
#include <iostream>
#include <fstream>

typedef struct Question Question;
#define NANSWERS 5
#define QUEST_SIZE 512
#define ANSWER_SIZE 256
#define MAGIC 0x61
#define QUIZVER "QUIZ001"
struct Question
{
	char question[QUEST_SIZE];
	char answers[NANSWERS][ANSWER_SIZE];
	int answer;
	int choice;
};

const Question EmptyQuestion = {"", {"", "", "", "", ""}, -1, -1};

#define FOREACH(i) for(int i = 0; i < NANSWERS; i++)

void magic(char *elem, unsigned int size);

template<class Container>
int questions_load(const char *filename, Container &questions)
{
	typename Container::value_type T;
	std::fstream ifs(filename, std::ios::in | std::ios::binary);
	if(!ifs) return -1;
	
	char s[sizeof(QUIZVER)];
	ifs.read(s, static_cast<std::streamsize>(std::strlen(QUIZVER)));
	if(std::strncmp(s, QUIZVER, std::strlen(QUIZVER)) != 0) {
		return -1;
	}
	typename Container::value_type q;
	while(ifs.read(reinterpret_cast<char*>(&q), sizeof(T)))
	{
		magic(reinterpret_cast<char*>(&q), sizeof(T));
		questions.push_back(q);
	}
	return (questions.size() == 0) ? -1 : 0;
}

template<class Container>
int questions_save(const char *filename, const Container &questions)
{
	typename Container::value_type T;
	std::ofstream out(filename, std::ios::out | std::ios::binary);
	if(!out) return -1;
	
	out.write(QUIZVER, static_cast<std::streamsize>(std::strlen(QUIZVER)));

	Container::const_iterator it;
	for(it = questions.begin(); it != questions.end(); ++it)
	{
		typename Container::value_type q = *it;
		magic(reinterpret_cast<char*>(&q), sizeof(T));
		out.write(reinterpret_cast<const char*>(&q), sizeof(T));
	}
	return 0;
}

#endif