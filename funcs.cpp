//https://contest.yandex.ru/contest/27665/problems/J/

#include "funcs.h"
#include <bits/stdc++.h>

bool canBeId(bool digitCanBeFirst, const std::string & word){
    if(word.empty())
        return false;
    if(!digitCanBeFirst && isdigit(word[0]))
        return false;
    return std::all_of(word.begin(), word.end(),
                       [](auto c){
                           return c == '_' || isdigit(c) || isalpha(c);
                       });
}

std::string tolower(const std::string & word){
    std::string ans = word;
    std::for_each(ans.begin(),ans.end(),[](auto & c){
        c = tolower(c);
    });
    return ans;
}

std::list<std::string> readCode(std::istream & input){
    std::list<std::string> ans;
    char c;
    std::string curWord;
    while (input.get(c)){
        if(c == '_' || isdigit(c) || isalpha(c))
            curWord.push_back(c);
        else{
            if(!curWord.empty())
                ans.push_back(curWord);
            curWord.clear();
        }
    }
    if(!curWord.empty()) ans.push_back(curWord);
    return ans;
}

void parseFile(std::istream & input, std::ostream & output){

    //! @brief word - stress letters indexes
    std::map<std::string, std::set<unsigned int>> dict;

    unsigned int N;
    std::string sCaseSensetive, sDigitCanBeFirst;
    bool caseSensetive, digitCanBeFirst;
    input >> N >> sCaseSensetive >> sDigitCanBeFirst;
    caseSensetive = sCaseSensetive == "yes";
    digitCanBeFirst = sDigitCanBeFirst == "yes";

    std::unordered_set<std::string> keyWords;
    std::string word;
    for(unsigned int i = 0; i<N; ++i){
        input >> word;
        if(canBeId(digitCanBeFirst,word)){
            if(!caseSensetive)
                word = tolower(word);
            keyWords.insert(word);
        }
    }

    auto code = readCode(input);

    //! @brief id - < count - first met >
    std::map<std::string,
        std::pair<unsigned long long int, unsigned long long int> > ids;

    std::for_each(code.begin(), code.end(),
                  [&caseSensetive,&digitCanBeFirst,&keyWords,&ids](auto & w){
        if(!canBeId(digitCanBeFirst,w))
            return;
        if(!caseSensetive)
            w = tolower(w);
        if(keyWords.count(w))
            return;
        if(!ids.count(w))
            ids[w] = { 0, ids.size()};
        ++ids[w].first;
    });

    auto mostFrequentWord = std::max_element(ids.begin(), ids.end(),
                                             [](const auto & id1, const auto & id2){
        //id1 < id2
        if(id1.second.first == id2.second.first)
            return id2.second.second < id1.second.second;
        return id1.second.first < id2.second.first;
    })->first;

    output << mostFrequentWord;
}
