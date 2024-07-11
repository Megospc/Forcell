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

    string EncodeConnections(int* data, uint size) {
        string res = "";

        for (uint j = 0; j < size; j++) {
            res += (data[j] < 0 || data[j] >= 10 ? "-":
                std::to_string(data[j]))+" ";
        }

        return res;
    }

    #define TABLE_ENCODER(name, len, code) { \
        uint size = len; \
        for (uint i = 0; i < size; i++) { \
            str += KeyVal(name+std::to_string(i), code); \
        } \
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
        if (string(rule->creator).length() > 0) str += KeyVal("creator", string(rule->creator));
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

        TABLE_ENCODER("force", rule->types, EncodeRow(&rule->forces[10*i], size, "%.2f"));
        TABLE_ENCODER("zone", rule->types, EncodeRow(&rule->zones[10*i], size, "%.0f"));

        if (rule->secondtable) {
            str += KeyVal("second-table", "");

            TABLE_ENCODER("2force", rule->types, EncodeRow(&rule->forces2[10*i], size, "%.2f"));
            TABLE_ENCODER("2zone", rule->types, EncodeRow(&rule->zones2[10*i], size, "%.0f"));
        }

        str += KeyVal("freqs", EncodeRow(rule->freqs, rule->types, "%.2f"));

        if (rule->connections) {
            str += KeyVal("connections", "");
            str += KeyVal("connection-attraction", rule->connectionAttraction, "%.3f");
            str += KeyVal("connection-replusion", rule->connectionReplusion, "%.3f");
            str += KeyVal("connection-distance", rule->connectionDistance, "%.0f");
            str += KeyVal("connection-normal", rule->connectionNormal, "%.0f");
            str += KeyVal("connection-max", rule->connectionMax, "%.0f");

            TABLE_ENCODER("connections", 10, EncodeConnections(&rule->connectionsPriority[10*i], size));
        }

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

    void DecodeConnections(string str, int* data) {
        string line = "";

        uint k = 0;

        for (uint i = 0; i < str.length(); i++) {
            char c = str[i];

            if (c == ' ') {
                if (line == "-") data[k++] = -1;
                else data[k++] = stoi(line);

                line = "";
            } else line += c;
        }

        if (line.length() > 0) data[k++] = stof(line);
    }

    #define KEYVAL_HANDLER(val, code) if (keyval.key == val) { code; continue; };

    #define TABLE_HANDLER(name, code) if (isStartsWith(keyval.key, name)) { \
        string val = keyval.val; \
        uint idx = stoi(keyval.key.substr(string(name).length())); \
        code; \
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

                line = "";

                KEYVAL_HANDLER("types", rule->types = stoi(keyval.val))
                KEYVAL_HANDLER("friction", rule->friction = stof(keyval.val))
                KEYVAL_HANDLER("attractor", rule->attractor = stof(keyval.val))
                KEYVAL_HANDLER("bounce-force", rule->bounceForce = stof(keyval.val))
                KEYVAL_HANDLER("second-table", rule->secondtable = true)
                KEYVAL_HANDLER("connections", rule->connections = true)
                KEYVAL_HANDLER("freqs", DecodeRow(keyval.val, rule->freqs))
                KEYVAL_HANDLER("connection-attraction", rule->connectionAttraction = stof(keyval.val))
                KEYVAL_HANDLER("connection-replusion", rule->connectionReplusion = stof(keyval.val))
                KEYVAL_HANDLER("connection-distance", rule->connectionDistance = stof(keyval.val))
                KEYVAL_HANDLER("connection-normal", rule->connectionNormal = stof(keyval.val))
                KEYVAL_HANDLER("connection-max", rule->connectionMax = stof(keyval.val))

                KEYVAL_HANDLER("type-force", {
                    if (keyval.val == "forcell") rule->forcetype = 0;
                    if (keyval.val == "classic") rule->forcetype = 2;
                    if (keyval.val == "constant") rule->forcetype = 1;
                })

                KEYVAL_HANDLER("name", writeStringToChar(rule->name, keyval.val));
                KEYVAL_HANDLER("creator", writeStringToChar(rule->creator, keyval.val));

                KEYVAL_HANDLER("lastupdate", {
                    const time_t time = stol(keyval.val);
                    const tm* tm = std::localtime(&time);

                    std::strftime(rule->lastupdate, 256, "%d %b %Y %H:%M:%S", tm);
                })

                TABLE_HANDLER("force", DecodeRow(val, &rule->forces[idx*10]))
                TABLE_HANDLER("zone", DecodeRow(val, &rule->zones[idx*10]))
                TABLE_HANDLER("2force", DecodeRow(val, &rule->forces2[idx*10]))
                TABLE_HANDLER("2zone", DecodeRow(val, &rule->zones2[idx*10]))
                TABLE_HANDLER("connections", DecodeConnections(val, &rule->connectionsPriority[idx*10]))
            } else if (c != '\r') line += c;
        }
    }
}