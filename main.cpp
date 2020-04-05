#include <iostream>
#include <iterator>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
class Data{
public:
    ifstream& stream;
    Data(ifstream& stream1):stream(stream1){}
    virtual ~Data(){}
    virtual queue<string> line()=0;
    virtual ofstream& write(ofstream &out){
        queue<string> result_line=line();
        while(out){
            out<<result_line<<endl;
        }
        return out;
    }
};


class File : public Data {
public:
    File(ifstream &stream) : Data(stream){}
    virtual queue<string> line() override{
        queue<string> resultLine;
        string resultString;
        while(stream){
            getline(stream, resultString);
            resultLine.push(resultString);
        }
        return resultLine;
    }
};

class DataDecorator : public Data{
protected:
    Data* source;
public:
    DataDecorator(Data* source){
        this->source=source;
    }
};

class HTMLDecorator : public DataDecorator{
private:
    string changeInHTML(string line){
        string newLine;
        bool regularLine = 0;
        for(char charLine : line){
            if(charLine=='\'')
                newLine+="&#39";
            else{
                if (charLine=='&')
                    newLine+="&amp";
                else{
                    if (charLine=='<')
                        newLine+="&lt";
                    else{
                        if (charLine=='>')
                            newLine+="&gt";
                        else{
                            if (charLine=='"')
                                newLine+="&quot";
                            else
                            newLine+=newLine;
                            }
                        }
                    }
                }
        }
        return newLine;
    }
public:
    HTMLDecorator(Data *source):DataDecorator(source){}
    virtual queue<string> line() override{
        queue<string> resultLine;
        string temp;
        string tagOpen [3] = {"<html>","<body>","<pre>"};
        for(int i=0;i<3;i++)
            resultLine.push(tagOpen[i]);
        while (source) {
            getline(source, temp);
            resultLine.push(changeInHTML(temp));
        }
        string tagClose[3] = {"</pre>","</body>","</html>"};
        for(int i=0;i<3;i++)
            resultLine.push(tagOpen[i]);
        return resultLine;
    }
};

class LineDecorator : public DataDecorator{
private:
    string changeInHTML(string line, int i){
        char temp[4];
        temp[0] = (char)i;
        temp[1] = ' ';
        temp[2] = '|';
        temp[3] = ' ';
        return line.insert(0,temp);
    }
public:
    LineDecorator(Data *source):DataDecorator(source){}
    queue<string> line() override{
        queue<string> resultLine;
        string temp;
        string tagOpen [3] = {"<html>","<body>","<pre>"};
        for(int i=0;i<3;i++)
            resultLine.push(tagOpen[i]);
        int i=1;
        while (source) {
            getline(source, temp);
            resultLine.push(changeInHTML(temp,i));
        }
        string tagClose[3] = {"</pre>","</body>","</html>"};
        for(int i=0;i<3;i++)
            resultLine.push(tagOpen[i]);
        return resultLine;
    }
};

/*class СPPDecorator : public DataDecorator{
private:
    string changeColour(string line,string word, string type){
        int pos;
        if(type == "type"){
            pos = line.find(word, 0);
            line.insert(pos, 1, '<font ');
        }

    }
    string changeInHTML(string line){
        string newLine;
        int posLine=0;
        while(line.find("bool", 0)) {
            if (line.find("void", 0)){
                line=changeColour(line,"void","type");
                        //int pos = line.find("void", 0);
                        //line.insert(pos, 1, '<font ');
            }
            if (line.find("bool", 0)){

            }
        }
        return newLine;
    }
public:
    СPPDecorator(Data *source):DataDecorator(source){}
    queue<string> line() override{
        queue<string> line() override{
                queue<string> resultLine;
                string temp;
                string tagOpen [3] = {"<html>","<body>","<pre>"};
                for(int i=0;i<3;i++)
                resultLine.push(tagOpen[i]);
                int i=1;
                while (source) {
                    getline(source, temp);
                    resultLine.push(changeInHTML());
                }
                string tagClose[3] = {"</pre>","</body>","</html>"};
                for(int i=0;i<3;i++)
                resultLine.push(tagOpen[i]);
                return resultLine;
        }
    }
};*/

void rewriting(queue<string> Q)
{
    std::fstream in("C:\\Users\\milpa\\CLionProjects\\8\\Text.txt", std::ios::in);
    in.close();
    in.open("C:\\Users\\milpa\\CLionProjects\\8\\Text.txt", std::ios::out | std::ios::in);
    ofstream fout;
    fout.open("C:\\Users\\milpa\\CLionProjects\\8\\Text.txt");
    std::ifstream into("C:\\Users\\milpa\\CLionProjects\\8\\Text.txt");
    for_each(istream_iterator<string>(into),istream_iterator<string>(),[&Q](string temp)
                  {
                      Q.push(temp);
                  });
    fout.close();

}

int main(int argc, char* argv[]) {
    ifstream inf;
    inf.open("C:\\Users\\milpa\\CLionProjects\\8\\Text.txt");
    if(!inf){
        cout<<"Test.txt could not be open for reading!"<<endl;
        return 1;
    }
    while(inf){
        string strInput;
        //getline(inf, source.write(inf));
       // queue<string> text;
        //text.push(strInput);
       // cout<<strInput<<endl;
    }
    return 0;
}
