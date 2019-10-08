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
	Song *curr_song;
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

	void select_song(int tag);	//selects the song to be played

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
		current_song = NULL;
	}
};

void Playlist::next_song(Song *s){
	if(s->next==NULL)
	{
		select_song(1);
	}
	current_song = s->next;
	play(current_song->song_loc);
}

void Playlist::previous_song(Song *s){
	if(s->prev==NULL)
	{
		select_song(tail->tag);
	}
	current_song = s->prev;
	play(current_song->song_loc);
}

void Playlist::select_song(int input_tag){
	if(input_tag>tail->tag)
	{
		cout<<"Invalid Option.\n";
		return;
	}
	Song *temp;
	temp = head;
	while(temp->tag!=input_tag)
	{
		temp = temp->next;
	}
	current_song = temp;
	play(temp->song_loc);
}


void Playlist::play(string song_loc){
	int k;
	char *cstr = new char[song_loc.length() + 1];
	strcpy(cstr, song_loc.c_str());
	PlaySound(cstr, NULL,SND_ASYNC );
	cout<<"Enter the desired option:\n";
	cout<<"1. Play Next Song.\n";
	cout<<"2. Play Previous Song.\n";
	cout<<"3. Play Another song.\n";
	cout<<"4. Stop song and go back to menu.\n";
	cin>>k;
	switch(k)
	{
	case 1:
		next_song(current_song);
		break;

	case 2:
		previous_song(current_song);
		break;

	case 3:
		stop();
		cout<<"Enter the Serial Number of the song you want to play:\n";
		int k;
		cin>>k;
		select_song(k);
		break;

	case 4:
		stop();
		break;

	default:
		break;
	}
}

void Playlist::stop(){
	PlaySound(NULL, 0, 0);
}


void Playlist::add_song(){
	ofstream fout;
	Song* new1 = new Song;
	cin.ignore();
	cout<<"Enter the song's title"<<endl;
	getline(cin, new1->song_name);
	cout<<"Enter the song's directory:"<<endl;
	getline(cin, new1->song_loc);
	fout.open("myplaylist.txt", ios::app);
	fout<<'\n'<<new1->song_name<<","<<new1->song_loc;
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

void Playlist::delete_song(int tag){
	if(head==NULL){
		cout<<"Playlist empty, cannot perform delete operation."<<endl;
	}
	else{
		Song*temp;
		Song*temp2;
		Song*Previous=NULL;
		int song_count = tail->tag;

		if(head->next == NULL){
			delete head;
		}
		else{
			temp = head;
			temp2 = temp;
			if(tag>song_count){
				cout<<"Invalid choice, the tag does not exist."<<endl;
			}
			else if(tag==1){
				head = head->next;
				head->prev = NULL;
				while(temp2 != NULL){
					temp2->tag--;
					temp2 = temp2->next;
				}
				temp->next = NULL;
				delete temp;
			}
			else{
				for(int i=1;i<tag;i++){
					Previous = temp;
					temp = temp->next;
				}
				temp2 = Previous->next;
						while(temp2 != NULL){
							temp2->tag--;
							temp2 = temp2->next;
						}
				if(temp->next == NULL){
					Previous->next = NULL;
				}
				else{
					Previous->next = temp->next;
					temp->next->prev = Previous;
				}
				temp->next = NULL;
				temp->prev = NULL;
				delete temp;
			}
		}
		 // open file in read mode or in mode
			ifstream is("myplaylist.txt");

			// open file in write mode or out mode
			ofstream ofs;
			ofs.open("temp.txt", ofstream::out);

			// loop getting single characters
			char c;
			int line_no = 1;
			while (is.get(c))
			{
				// if a newline character
				if (c == '\n')
				line_no++;

				// file content not to be deleted
				if (line_no != tag)
					ofs << c;
			}

			// closing output file
			ofs.close();

			// closing input file
			is.close();

			// remove the original file
			remove("myplaylist.txt");

			// rename the file
			rename("temp.txt", "myplaylist.txt");
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
	if(head==NULL)
	{
		cout<<"The playlist is empty. Please add a new song.\n";
	}
}

void Playlist::display(){
	Song*t;
	t = head;
	while(t!=NULL){
		cout<<t->tag<<'\t'<<t->song_name<<endl;
		t = t->next;
	}
}

int main(int argc, char* argv[])
{
	Playlist p;
	p.readfromfile();
	int n=0;
	do{
	cout<<"                                             Your Playlist\n";
	cout<<"__________________________________________________________________"<<endl;
	cout<<"List of songs in the Playlist:\n";
	p.display();
	cout<<"Enter the desired choice:\n";
	cout<<"1. Add a new song.\n";
	cout<<"2. Delete an existing song.\n";
	cout<<"3. Play a song.\n";
	cout<<"4. Exit.\n";
	cout<<"__________________________________________________________________"<<endl;
	cin>>n;
	switch(n)
	{
		case 1:
			p.add_song();
			break;

		case 2:
			int y;
			cout<<"Enter the Serial Number of the song you want deleted:\n";
			cin>>y;
			p.delete_song(y);
			break;

		case 3:
			int x;
			cout<<"Enter the Serial Number of the song you want to play:\n";
			cin>>x;
			p.select_song(x);
			break;

		default:
			break;
	}
}
	while(n!=4);
return 0;
}
