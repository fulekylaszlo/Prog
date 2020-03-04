#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace std;
void readJavaExt ( boost::filesystem::path path, vector<string> & classes )
{
        if ( is_regular_file ( path ) )
        {
                std::string ext ( ".java" );
                if ( !ext.compare ( boost::filesystem::extension ( path ) ) )
                {
                        classes.push_back(path.string());
                }
        }
        else if ( is_directory ( path ) )
            for ( boost::filesystem::directory_entry & entry : boost::filesystem::directory_iterator ( path ) )
                readJavaExt ( entry.path(), classes );
}
vector<string> getClass (string path)
{
    vector <string> classes;
    boost::filesystem::path root (path);
    
    readJavaExt(root, classes);
    
    return classes;
}
int main(int argc, char const * argv[])
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    string root = full_path.string() + "/" + "src";
    vector<string> roots = {root};
    vector<string> classes = getClass ( root );
    
    for(const auto & i : classes)
    {
        cout << i << endl;
    }
    cout << "------------------------------------------------------------------\n";
    cout << "Összesen " << classes.size() << " .java file található az src-ben.\n";
    return 0;
}
