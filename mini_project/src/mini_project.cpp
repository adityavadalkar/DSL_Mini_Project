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
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
using namespace std;

class Song{
	std::string song_loc;
	std::string song_name;
	int tag;
	Song *next;
	Song *prev;
	friend class Playlist;
public:
	Song(){
		next = prev = NULL;
	}
};


class Playlist{
	string name;
	Song *current_song;
	friend class Song;
	Song *head;
	Song *tail;
public:
	void add_song(); //adds song at the end of linked list

	void swap_song();		//changes the position of a song in the playlist

	void delete_song(int tag);	//deletes a song from the playlist

	void select_song(int input_tag);	//selects the song to be played

	void display(); //Displays the playlist

	void readfromfile(); //Reads the playlist from a (.txt) file at the start of the program and creates a LL

	void play(string song_loc);

	void stop();

	void next_song(Song *s);

	void previous_song(Song *s);

	Playlist(){
		name = "New Playlist";
		head = NULL;
		tail = NULL;
	}
};

void Playlist::next_song(Song *s){
	current_song = s->next;
	play(current_song->song_loc);
}

void Playlist::previous_song(Song *s){
	current_song = s->prev;
	play(current_song->song_loc);
}


void Playlist::play(string song_loc){
	char k;
	char *cstr = new char[song_loc.length() + 1];
	strcpy(cstr, song_loc.c_str());
	PlaySound(cstr, NULL,SND_ASYNC );
	cout<<"Press n for next song or p for previous song:\n";
	cin>>k;
	switch(k)
	{
	case 'n':
		next_song(current_song);
		break;

	case 'p':
		previous_song(current_song);
		break;

	default:
		break;
	}
}

void Playlist::stop(){
	PlaySound(NULL, 0, 0);
}

void Playlist::select_song(int input_tag){
	Song *temp;
	temp = head;
	while(temp->tag!=input_tag)
	{
		temp = temp->next;
	}
	current_song = temp;
	play(temp->song_loc);
}

void Playlist::add_song(){
	ofstream fout;
	Song* new1 = new Song;
	cout<<"Enter the song's title"<<endl;
	getline(cin, new1->song_name);
	cout<<"Enter the song's directory:"<<endl;
	getline(cin, new1->song_loc);
	fout.open("myplaylist.txt", ios::app);
	fout<<new1->song_name<<","<<new1->song_loc<<endl;
	fout.close();
	if(head==NULL){
		head = new1;
		tail = new1;
		new1->tag = 1;
	}
	else{
	new1->tag = (tail->tag)+1;
	tail->next = new1;
	new1->prev = tail;
	tail = new1;
	}
}



void Playlist::readfromfile(){
	ifstream myfile;
	myfile.open("myplaylist.txt");
	string inp;
	while(getline(myfile, inp)){
		Song* new1 = new Song;
		char delimiter = ',';
		new1->song_name = inp.substr(0, inp.find(delimiter));
		new1->song_loc = inp.substr(inp.find(delimiter)+1, inp.length());
		if(head==NULL){
			head = new1;
			tail = new1;
			new1->tag = 1;
		}
		else{
		new1->tag = (tail->tag)+1;
		tail->next = new1;
		new1->prev = tail;
		tail = new1;
		}

	}
}


/*void Playlist::swap_song(){
	cout<<"Enter the tag of the song to be swapped"<<endl;
	Song* temp;
	cin>>temp->tag;
	//for(int i=0;i<)
}*/

void Playlist::display(){
	Song*t;
	t = head;
	while(t!=NULL){
		cout<<t->tag<<'\t'<<t->song_name<<'\t'<<t->song_loc<<endl;
		t = t->next;
	}
}

int main(int argc, char* argv[])
{
	Playlist p;
	//p.add_song();
	p.readfromfile();
	p.display();
	cout<<"Select the song to play\n";
	int n;
	cin>>n;
	p.select_song(n);

	//p.add_song();
	//p.play("C:\\Users\\Tanmay\\Desktop\\Alesis-Fusion-Acoustic-Bass-C2.wav");
	//p.display();
	/*int n;
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
	}*/
	 //SND_FILENAME or SND_LOOP
return 0;
}
