#include "Tweet.h"

Tweet::Tweet(string text, const vector<string> &users) {
    this->text = text;

    vector<string> menciones = getMentions();
    for(unsigned int i = 0; i < users.size(); i++) {
        bool excepcion = true;
        for(unsigned int j = 0; j < menciones.size(); j++) {
            if(menciones[j] == users[i])
                excepcion = false;
        }
        if(excepcion)
            throw exception_mention;
    }

    this->id = nextId;
    nextId = nextId + 1;
}

string Tweet::getText() const {
    return text;
}

unsigned int Tweet::getId() const {
    return id;
}

vector<string> Tweet::getMentions() const {
    vector<string> menciones;

    for(unsigned int i = 0; i < text.size(); i++) {
        if(text[i]=='@') {
            string username;
            bool coincidencia = false;
            for(unsigned int j = i + 1; j < text.size(); j++) {
                if(isalnum(text[j])) {
                    username.push_back(text[j]);
                } else {
                    i = j;
                    break;
                }
            }
            for(unsigned int i = 0; i < menciones.size(); i++) {
                if(menciones[i] == username)
                    coincidencia = true;
            }
            if(!coincidencia)
                menciones.push_back(username);
        }
    }

    return menciones;
}

ostream& operator<<(ostream &os, const Tweet &tw) {
    os << "[" << tw.id << "] " << tw.text << endl;
    return os;
}