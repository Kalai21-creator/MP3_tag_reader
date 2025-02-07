# MP3 Tag Reader Project Documentation

## Project Overview
The MP3 Tag Reader project is a desktop-based software written in C. It reads and displays MP3 (ID3) tag information from MP3 files. The project is designed for users who wish to view or collect MP3 tag data and can be extended to include a tag editor for modifying MP3 tag information.

---

## Features
The application supports the following functionalities:

### Mandatory Features
- **ID3 Version Handling:**
  - Support for all ID3 versions except v2.4.
  - Display the version of the ID3 tag used.

- **Metadata Display:**
  - Display all metadata information from the ID3 tag, including title, artist, album, track number, and more.

- **Tag Modification:**
  - Allow users to change tags based on given options.

- **Help Screen:**
  - Display a help screen when the `-h` option is provided.

- **Image Details:**
  - If an image is embedded in the file, display details such as type, path, and size.

- **Error Handling:**
  - Display proper error messages if the ID3 tag is not found.

### Additional Features
- **Album Art Extraction:**
  - Provide an option to extract the album art (image) from the file.

- **Tag Deletion:**
  - Add an option to delete all tag data from the file.

- **ID3v2.4 Support:**
  - Incorporate handling for the ID3v2.4 version.

- **Selective Tag Deletion:**
  - Allow deletion of selected tags using specific options.

---

## Understanding the ID3 Standard and Tags
### ID3v1
- Total of 128 bytes used for metadata storage.
- Fields include title, artist, album, and track number.
- The last three bytes are always "TAG," identifying it as an ID3 tag.
- Remaining unused bytes are filled with binary value 0.

### ID3v2
- Starts with a tag header followed by one or more frames.
- Tag signature code is "ID3x" where `x` denotes the sub-version number.
- Found typically at the beginning of an MP3 file.

#### ID3v2 Frame Header Details
- **ID3v2 Version:** `$03 00` (versions 2, 3, or 4)
- **Flags:** `%abc00000`
- **Size:** `4 * %0xxxxxxx` (Total size of the ID3 tag)

#### ID3v2.2 Frame Header
- **Frame ID:** `$xx xx xx` (Three characters) [e.g., TAL for Album/Movie/Show Title]
- **Original Artist:** TOA
- **Size:** `$xx xx xx`

#### ID3v2.3 or ID3v2.4 Frame Header
- **Frame ID:** `$xx xx xx xx` (Four characters) [e.g., TIT2 for Title/Song Name/Content Description]
- **Size:** `$xx xx xx xx`
- **Flags:** `$xx xx`

---

## Building and Running the Project

### Compilation
To compile the project, use the following command:
```bash
gcc -o mp3_tag_reader mp3_tag_reader.c
```

### Running the Application
```bash
./mp3_tag_reader [options] <file>
```

### Command Line Options
- `-h`: Display help screen
- `-v`: Display version of the ID3 tag
- `-m`: Modify tag information
- `-e`: Extract album art
- `-d`: Delete all tag data
- `-r`: Delete a specific tag

### Sample Usage
1. Display help screen:
   ```bash
   ./mp3_tag_reader -h
   ```

2. View metadata from an MP3 file:
   ```bash
   ./mp3_tag_reader -v my_song.mp3
   ```

3. Modify tag information:
   ```bash
   ./mp3_tag_reader -m my_song.mp3
   ```

4. Extract album art:
   ```bash
   ./mp3_tag_reader -e my_song.mp3
   ```

5. Delete all tag data:
   ```bash
   ./mp3_tag_reader -d my_song.mp3
   ```
