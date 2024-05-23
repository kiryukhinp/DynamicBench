#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>
#include <vector>
#include <fstream>
#include <cmath>

struct Value
{
    double v; //x
    double u; //uncertainty
};

inline auto lerp(double x, double y1, double y2, double x1, double x2)->double
{
    return y1 + (x - x1)*(y2 - y1)/(x2 - x1);
}

inline auto trim(std::string const &st)->std::string
{
    size_t sb = st.find_first_not_of(' '), se = st.find_last_not_of(' ');
    return st.substr(sb, se - sb + 1);
}

inline auto ltrim(std::string const &st)->std::string
{
    size_t sb = st.find_first_not_of(' ');
    return st.substr(sb);
}

inline auto rtrim(std::string const &st)->std::string
{
    size_t se = st.find_last_not_of(' ');
    return st.substr(0, se + 1);
}

inline auto in(std::string const &st1, std::string const &st2)->bool
{
    return st1.find(st2) != std::string::npos;
}

inline auto in(std::string const &st1, char st2)->bool
{
    return st1.find(st2) != std::string::npos;
}

inline auto getline(std::ifstream &iFile)->std::string
{
    std::string buf;
    std::getline(iFile, buf);
    return buf;
}

inline void skipline(std::ifstream &iFile, size_t am = 1)
{
    std::string buf;
    for(int i = 0; i < am; ++i)
        std::getline(iFile, buf);
}

inline auto split(std::string const &st, char sep = ' ')->std::vector<std::string>
{
    std::string buf = trim(st);
    std::vector<std::string> vbuf;
    size_t sb = 0;

    if(buf.length() == 0)
        return vbuf;

    for(int i = 1; i < buf.length(); ++i)
    {
        if(buf[i] == sep && buf[i - 1] != sep)
        {
            vbuf.push_back(trim(buf.substr(sb, i - sb)));
            sb = i + 1;
        }
        if(i == buf.length() - 1 && buf[i] != sep)
            vbuf.push_back(trim(buf.substr(sb)));
    }
    return vbuf;
}

inline auto vostovod(std::vector<std::string> const &vos)->std::vector<double>
{
    std::vector<double> vod;
    vod.reserve(vos.size());
    for(auto const &s: vos)
        vod.push_back(std::stod(s));
    return vod;
}

inline auto vostovoi(std::vector<std::string> const &vos)->std::vector<int>
{
    std::vector<int> voi;
    voi.reserve(vos.size());
    for(auto const &s: vos)
        voi.push_back(std::stoi(s));
    return voi;
}

inline auto asttovos(std::string const &str, size_t cutFirst = 0)->std::vector<std::string>
{
    std::vector<std::string> res;
    auto data = split(str);
    for(size_t i = cutFirst; i < data.size(); ++i)
    {
        if(split(data[i], '*').size() < 2)
            res.push_back(data[i]);
        else
        {
            auto buf = std::vector<std::string>(std::stoi(split(data[i], '*')[0]), split(data[i], '*')[1]);
            res.insert(res.end(), buf.begin(), buf.end());
        }
    }
    return res;
}

inline auto file_to_vos(std::string const &fileName)->std::vector<std::string>
{
    std::ifstream file(fileName);
    std::vector<std::string> data;
    std::string buf;
    while(!file.eof())
        buf += getline(file) + " ";
    file.close();
    return split(buf);
}

#endif /* AUXILIARY_H */
