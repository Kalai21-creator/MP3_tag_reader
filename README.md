# MP3 Tag Reader Project Documentation

## Project Overview
The MP3 Tag Reader project in C is a command-line application designed to read and display MP3 (ID3) tag information from MP3 files. This software is useful for individuals who wish to view and collect MP3 tag data, such as title, artist, album, and track information. The project can be extended to implement a tag editor, allowing users to modify MP3 tag information.

---

## Features
The application supports the following functionalities:

### Mandatory Features
- **ID3 Version Detection:**
  - Handle all ID3 versions except ID3v2.4.
  - Detect and display the ID3 tag version used in the MP3 file.

- **Metadata Display:**
  - Extract and display all metadata information, including title, artist, album, track number, and more.

- **Tag Editing:**
  - Allow users to modify existing tag information based on command-line options.

- **Help Screen:**
  - Display a help screen when the `-h` option is passed.

- **Image Information:**
  - Display details about any embedded image (type, path, and size).

- **Error Handling:**
  - Display appropriate error messages if no ID3 tag is found.

### Additional Features
- Extract album art (image) from the MP3 file.
- Delete all tag data from the file.
- Support for ID3v2.4.
- Option to delete specific tags.

---

## Understanding ID3 Tags
- **ID3v1:**
  - 128 bytes of metadata at the end of the MP3 file.
  - Fields include title, artist, album, year, and comment.

- **ID3v2:**
  - Flexible and complex format with a tag header and multiple frames.
  - Found at the beginning of the MP3 file.

- **Frame Header:**
  - Contains the frame ID, size, and flags.
  - Examples of frame IDs: `TIT2` (title), `TPE1` (artist), and `TALB` (album).

---

## Building and Running the Project

### Compilation
To compile the project, use the following command:
```bash
gcc -o mp3_tag_reader mp3_tag_reader.c
```

### Running the Application
```bash
./mp3_tag_reader [options] <mp3_file>
```

### Command Line Options
- `-h`: Display help screen
- `-r`: Read and display MP3 tag information
- `-e <field> <value>`: Edit a specific tag field
- `-d <field>`: Delete a specific tag field
- `-a`: Extract album art
- `-x`: Delete all tag data

### Sample Usage
1. Display help screen:
   ```bash
   ./mp3_tag_reader -h
   ```

2. Read and display MP3 tag information:
   ```bash
   ./mp3_tag_reader -r song.mp3
   ```

3. Edit the title tag:
   ```bash
   ./mp3_tag_reader -e TIT2 "New Song Title" song.mp3
   ```

4. Extract album art:
   ```bash
   ./mp3_tag_reader -a song.mp3
   ```

5. Delete a specific tag:
   ```bash
   ./mp3_tag_reader -d TIT2 song.mp3
   ```

6. Delete all tag data:
   ```bash
   ./mp3_tag_reader -x song.mp3
   ```

---

## Git Repository Setup
### README Template
```markdown
# MP3 Tag Reader Project

## Description
A command-line C application to read and edit MP3 (ID3) tag information.

## Features
- Handle all ID3 versions except v2.4
- Read and display metadata from MP3 files
- Edit or delete specific tags
- Extract album art
- Command-line interface for easy operation

## Compilation
```bash
gcc -o mp3_tag_reader mp3_tag_reader.c
```

## Usage
```bash
./mp3_tag_reader [options] <mp3_file>
```

## Command Line Options
- `-h`: Display help screen
- `-r`: Read and display MP3 tag information
- `-e <field> <value>`: Edit a specific tag field
- `-d <field>`: Delete a specific tag field
- `-a`: Extract album art
- `-x`: Delete all tag data

## Author
KALAIVANAN D
```

This project provides practical exposure to file operations, metadata handling, and command-line programming in C. Happy coding!
