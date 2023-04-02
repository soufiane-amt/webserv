#include <iostream>
#include <dirent.h>
#include <cstdlib> // for system()

using namespace std;

int main() {
    DIR *dir;
    struct dirent *ent;
    
    // Open the current directory
    dir = opendir("./www");
    if (dir == NULL) {
        cout << "Failed to open directory" << endl;
        return 1;
    }
    
    // Output the HTML header
    cout << "<html><head><title>Directory Listing</title></head><body>" << endl;
    cout << "<h1>Directory Listing</h1><hr>" << endl;
    
    // Output the list of files and directories in the directory as links
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_DIR) {
            // Output a link for a directory
            cout << "<a href=\"" << ent->d_name << "/\">" << ent->d_name << "/</a><br>" << endl;
        } else {
            // Output a link for a file
            cout << "<a href=\"" << ent->d_name << "\">" << ent->d_name << "</a><br>" << endl;
        }
    }
    
    // Output the HTML footer
    cout << "<hr></body></html>" << endl;
    
    // Close the directory
    closedir(dir);
    
    return 0;
}
