// Rule saver

#pragma once

#include "Definitions.h"
#include "Simulation.h"
#include "Files.h"

#include <nfd.h>

namespace Saver {
    string EncodeRow(float* data, uint size, cstr fmt) {
        string res = "";

        for (uint j = 0; j < size; j++) {
            res += floatString(data[j], fmt)+" ";
        }

        return res;
    }

    string EncodeTable(uint size, float* data, string name, cstr fmt) {
        string res = "";

        for (uint i = 0; i < size; i++) {
            res += KeyVal(name+std::to_string(i), EncodeRow(&data[10*i], size, fmt));
        }

        return res;
    }

    void Save(Simulation::Rule* rule) {
        string str = "";

        str += KeyVal("name", string(rule->name));
        str += KeyVal("creator", string(rule->creator));
        str += KeyVal("lastupdate", std::to_string(time(NULL)));

        str += KeyVal("types", rule->types);
        str += KeyVal("friction", rule->friction, "%.3f");
        str += KeyVal("attractor", rule->attractor, "%.5f");
        str += KeyVal("bounce-force", rule->bounceForce, "%.2f");

        string forcetype;

        switch (rule->forcetype) {
            case 0:
                forcetype = "forcell";
                break;
            case 2:
                forcetype = "classic";
                break;
            case 1:
                forcetype = "constant";
                break;
        }

        str += KeyVal("type-force", forcetype);

        str += EncodeTable(rule->types, rule->forces, "force", "%.2f");
        str += EncodeTable(rule->types, rule->zones, "zone", "%.0f");

        if (rule->secondtable) {
            str += KeyVal("second-table", "");

            str += EncodeTable(rule->types, rule->forces2, "2force", "%.2f");
            str += EncodeTable(rule->types, rule->zones2, "2zone", "%.0f");
        }

        str += KeyVal("freqs", EncodeRow(rule->freqs, rule->types, "%.2f"));

        File::Data data;
        data.data = str.data();
        data.length = str.length();

        nfdu8char_t* path;

        if (NFD_SaveDialog(&path, NULL, 0, ".", (string(rule->name)+".txt").c_str()) != NFD_OKAY) return;

        File::Write(path, data);

        NFD_FreePathU8(path);
    }

    void DecodeRow(string str, float* data) {
        string line = "";

        uint k = 0;

        for (uint i = 0; i < str.length(); i++) {
            char c = str[i];

            if (c == ' ') {
                data[k++] = stof(line);

                line = "";
            } else line += c;
        }

        if (line.length() > 0) data[k++] = stof(line);
    }

    void DecodeTable(KeyVal* keyval, float* data, string name) {
        if (isStartsWith(keyval->key, name)) DecodeRow(
            keyval->val,
            &data[stoi(keyval->key.substr(name.length()))*10]
        );
    }

    void Open(Simulation::Rule* rule) {
        nfdu8char_t* path;

        if (NFD_OpenDialog(&path, NULL, 0, ".") != NFD_OKAY) return;

        File::Data data = File::Read(path);

        NFD_FreePath(path);

        rule->forcetype = 0;

        writeStringToChar(rule->name, "Unnamed");
        writeStringToChar(rule->creator, "[not provided]");
        writeStringToChar(rule->lastupdate, "[not provided]");

        string line = "";

        for (uint i = 0; i < data.length; i++) {
            char c = data.data[i];

            if (c == '\n') {
                KeyVal keyval(line);

                if (keyval.key == "types") rule->types = stoi(keyval.val);
                if (keyval.key == "friction") rule->friction = stof(keyval.val);
                if (keyval.key == "attractor") rule->attractor = stof(keyval.val);
                if (keyval.key == "bounce-force") rule->bounceForce = stof(keyval.val);
                if (keyval.key == "second-table") rule->secondtable = true;
                if (keyval.key == "freqs") DecodeRow(keyval.val, rule->freqs);
                DecodeTable(&keyval, rule->forces, "force");
                DecodeTable(&keyval, rule->zones, "zone");
                DecodeTable(&keyval, rule->forces2, "2force");
                DecodeTable(&keyval, rule->zones2, "2zone");

                if (keyval.key == "type-force") {
                    if (keyval.val == "forcell") rule->forcetype = 0;
                    if (keyval.val == "classic") rule->forcetype = 2;
                    if (keyval.val == "constant") rule->forcetype = 1;
                }

                if (keyval.key == "name") writeStringToChar(rule->name, keyval.val);
                if (keyval.key == "creator") writeStringToChar(rule->creator, keyval.val);
                if (keyval.key == "lastupdate") {
                    const time_t time = stol(keyval.val);
                    const tm* tm = std::localtime(&time);

                    std::strftime(rule->lastupdate, 256, "%d %b %Y %H:%M:%S", tm);
                }

                line = "";
            } else if (c != '\r') line += c;
        }
    }
}