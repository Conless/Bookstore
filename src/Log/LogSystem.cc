#include "LogSystem.h"

#include <iomanip>
#include <ctime>
#include <utility>

namespace bookstore {

namespace log {

LogSystem::LogSystem() : fout("data/Bookstore.log") {
    fout.SetColor(RED);
    fout << "\n\n\n mmmmm   mmmm   mmmm  m    m  mmmm mmmmmmm  mmmm  mmmmm  "
            "mmmmmm\n";
    fout.SetColor(YELLOW);
    fout << " #    # m\"  \"m m\"  \"m #  m\"  #\"   \"   #    m\"  \"m #   "
            "\"# #     \n";
    fout.SetColor(GREEN);
    fout << " #mmmm\" #    # #    # #m#    \"#mmm    #    #    # #mmmm\" "
            "#mmmmm\n";
    fout.SetColor(CYAN);
    fout << " #    # #    # #    # #  #m      \"#   #    #    # #   \"m #     "
            "\n";
    fout.SetColor(BLUE);
    fout << " #mmmm\"  #mm#   #mm#  #   \"m \"mmm#\"   #     #mm#  #    \" "
            "#mmmmm\n";
    fout.SetColor(PURPLE);
    fout << "\n----------------Bookstore v0.2.0 output log----------------\n";
}

Printer& operator<<(Printer &out, const UserData &user) {
    if (user.second == 7) {
        out.SetColor(RED);
        out << "Manager";
        out.Reset();
    }
    else if (user.second == 3) {
        out.SetColor(CYAN);
        out << user.first;
        out.Reset();
    }
    else if (user.second == 1) {
        out.SetColor(BLUE);
        out << user.first;
        out.Reset();
    }
    else if (user.second == 0) {
        out.SetColor(GREEN);
        out << "Guest";
        out.Reset();
    }
    return out;
}

void LogSystem::WriteInput(const std::string &str) {
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);
    fout.SetColor(YELLOW);
    fout << '[';
    fout << std::setw(2) << std::setfill('0') << time_info->tm_hour;
    fout << ':';
    fout << std::setw(2) << std::setfill('0') << time_info->tm_min;
    fout << ':';
    fout << std::setw(2) << std::setfill('0') << time_info->tm_sec;
    fout << "] ";
    fout.Reset();
    fout << "> " << str << '\n';
}

void LogSystem::WriteInvalid(const std::string &str) {
    fout.SetColor(RED);
    fout << "\33[4m\33[1m\33[5mError: ";
    fout << str << "!!!\n";
    fout.Reset();
}

void LogSystem::WriteLog(const UserData &cur, const UserData &tmp, 
                         const bookstore::input::BookstoreParser &msg) {
    using namespace input;
    if (msg.func == SU) {
        fout << tmp << " login.";
    } else if (msg.func == LOGOUT) {
        fout << cur << " logout.";
    } else if (msg.func == REG) {
        fout << cur << " register a new user ";
        fout << tmp << ".";
    } else if (msg.func == PASSWD) {
        fout << cur << " modify ";
        fout << tmp << "'s password.";
    } else if (msg.func == USERADD) {
        fout << cur << " add a new user ";
        fout << tmp << ".";
    } else if (msg.func == DEL) {
        fout << cur << " delete the user ";
        fout << tmp << ".";
    } else if (msg.func == FINANCE) {
        if (msg.args.size())
            fout << cur << " query the finance data of last " << msg.args[0] << " transanctions.";
        else fout << cur << " query all the finance data.";
    } else if (msg.func == SHOW_ALL) {
        fout << cur << " query all the book data.";
    } else if (msg.func == SHOW_ISBN) {
        fout << cur << " query the book with ISBN " << msg.args[0] << ".";
    } else if (msg.func == SHOW_NAME) {
        fout << cur << " query the books called " << msg.args[0] << ".";
    } else if (msg.func == SHOW_AUTHOR) {
        fout << cur << " query the books written by " << msg.args[0] << ".";
    } else if (msg.func == SHOW_KEYWORD) {
        fout << cur << " query the books with the keyword " << msg.args[0] << ".";
    } else if (msg.func == BUY) {
        fout << cur << " buy " << msg.args[1] << " book";
        if (msg.args[0] != "1")
            fout << "s";
        fout << " with ISBN " << msg.args[0] << ".";
    } else if (msg.func == SEL) {
        fout << cur << " select book with ISBN " << msg.args[0] << ".";
    } else if (msg.func == MODIFY) {
        fout << cur << " modify the selected book into ";
        if (msg.args[0] != "")
            fout << "-ISBN=" << msg.args[0] << " ";
        if (msg.args[1] != "")
            fout << "-name=" << msg.args[1] << " ";
        if (msg.args[2] != "")
            fout << "-author=" << msg.args[2] << " ";
        if (msg.args[3] != "")
            fout << "-key=" << msg.args[3] << " ";
        if (msg.args[4] != "")
            fout << "-price=" << msg.args[4] << " ";
    } else if (msg.func == IMPORT) {
        fout << cur << " import " << msg.args[0] << " selected book";
        if (msg.args[0] != "1")
            fout << "s";
        fout << " which costs $" << msg.args[1] << ".";
    } else if (msg.func == LOG) {
        fout << cur << " query the log file.";
    }
    fout << '\n';
    fout.flush();
}

}

}