// main.cpp 2024/04/27 dwg - Copy Libation mp3 results to ~/AudioBooks
// Copyright (c) 2024 Douglas Goodall. All Rights Reserved.

// The purpose of this program is to extract the mp3 files from the results of
// the conversion of Audible proprietary .aax files into open source mp3 files.
// The program traverses the directories where the resultant files were placed
// by Libation during the processing phase.
// In this example, I had Libation buffer the Audible data on one of my spare
// SSD drives. I then transfer the resulting mp3 data to my Audiobooks
// high level folder in my home directory.

// The Libation application web site is:
//      https://getlibation.com/
// Fetch the Ubuntu Linux compatible binary like so:
//      wget https://github.com/rmcrackan/Libation/releases/tag/v11.1.0/Libation.11.1.0-linux-chardonay-amd64.deb
// And install it like so:
//      sudo dpkg -i Libation.11.1.0-linux-chardonnay-amd64.deb
// The boost libraries are also required and may be installed like so:
//      sudo apt install libboost-all-dev

#include <boost/filesystem.hpp>
#include <iostream>

int main() {
    // Define the source directory path
    boost::filesystem::path src_dir("/media/doug/SataSSD4/Liberation/");
    // Define the destination directory path
    boost::filesystem::path dest_dir("/home/doug/AudoBooks/");

    try {
        // Check whether the source directory path exists and whether it is indeed a directory
        if (boost::filesystem::exists(src_dir) && boost::filesystem::is_directory(src_dir)) {
            // Create a recursive_directory_iterator pointing to the end
            boost::filesystem::recursive_directory_iterator end_iter;
            // Loop through all files in the source directory, including those in nested directories
            for (boost::filesystem::recursive_directory_iterator dir_itr(src_dir); dir_itr != end_iter; ++dir_itr) {
                // Check if the current file is a regular file and if its extension is .mp3
                if (boost::filesystem::is_regular_file(dir_itr->path()) &&
                    dir_itr->path().extension() == ".mp3") {
                    // Construct the destination path
                    boost::filesystem::path dest_path = dest_dir / dir_itr->path().filename();
                    // Copy the file to the destination directory, overwriting a previous file with the same name if it exists
                    boost::filesystem::copy(dir_itr->path(), dest_path, boost::filesystem::copy_options::overwrite_existing);
                    // Print out which file was copied to where
                    std::cout << "Copied " << dir_itr->path().string() << " to " << dest_path.string() << std::endl;
                }
            }
        } else {
            // Inform the user if the source directory does not exist or is not a directory
            std::cout << src_dir << " does not exist or is not a directory." << std::endl;
        }
    } catch (const boost::filesystem::filesystem_error& ex) {
        // Catch and print any filesystem errors
        std::cout << ex.what() << std::endl;
    }
    return 0;
}

////////////////////
// eof - main.cpp //
////////////////////

