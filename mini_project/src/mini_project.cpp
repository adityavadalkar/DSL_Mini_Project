//============================================================================
// Name        : mini_project.cpp
// Author      : Aditya Vadalkar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<windows.h>
#include<mmsystem.h>
#include<string>
using namespace std;

class Song{
	std::string song_loc;
	std::string song_name;
	int tag;
	Song *next;
	Song *prev;
public:
	Song(){
		song_loc = '\0';
		tag =0;
		song_name = "New Song";
		next = prev = NULL;
	}

	void add_song(string song_location);		//adds song at the end of linked list

	void swap_song(int location);		//changes the position of a song in the playlist

	void delete_song(int tag);	//deletes a song from the playlist

	void select_song(int tag);	//selects the song to be played

	void shuffle_play();	//arranges the songs in a random order in the playlist
	
	void play(string song_loc);	//plays the song

	void stop();		//stops the song


};

class Playlist{
	string name;
public:
	Playlist(){
		name = 'New Playlist';
	}
};

void Song::play(string song_loc){
	char k;
	char *cstr = new char[song_loc.length() + 1];
	strcpy(cstr, song_loc.c_str());
	PlaySound(cstr, NULL,SND_ASYNC );
	cout<<"Enter any character to stop:\n";
	cin>>k;
	if(k=='n')
		stop();
	else play(song_loc);
}

void Song::stop(){
	PlaySound(NULL, 0, 0);
}

int main(int argc, char* argv[])
{
	int n;
	cout<<"Enter the song you want to be played:\n";
	cin>>n;
	switch(n)
	{
	case 1:
		PlaySound("D:\\yes-hahahaa.wav", NULL, SND_LOOP);
		break;

	case 2:
		PlaySound("D:\\03-Unfaithful.wav", NULL, SND_FILENAME);
		break;

	default:
		break;
	}
	 //SND_FILENAME or SND_LOOP
return 0;
}
