#include "stdafx.h"
#include "question.h"

void magic(char *elem, unsigned int size)
{
	for(unsigned i = 0; i < size; i++)
		elem[i] ^= MAGIC;
}
/*
int questions_load(const char *filename, std::vector<Question> &questions) {
	std::fstream ifs(filename, std::ios::in | std::ios::binary);
	if(!ifs) return -1;
	
	Question q;
	while(ifs.read(reinterpret_cast<char*>(&q), sizeof(Question)))
	{
		magic(reinterpret_cast<char*>(&q), sizeof(Question));
		questions.push_back(q);
	}
	return (questions.size() == 0) ? -1 : 0;
}

int questions_save(const char *filename, const std::vector<Question> &questions)
{
	std::ofstream out(filename, std::ios::out | std::ios::binary);
	if(!out) return -1;
	
	std::vector<Question>::const_iterator it;
	for(it = questions.begin(); it != questions.end(); ++it)
	{
		Question q = *it;
		magic(reinterpret_cast<char*>(&q), sizeof(Question));
		out.write(reinterpret_cast<const char*>(&q), sizeof(Question));
	}
	return 0;
}
*/