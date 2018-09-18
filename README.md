# wcompress

wcompress is a compressor/minifier for HTML, CSS and JS files. Unlike many compressors, wcompress run on Linux Terminal. It compresses the specific input file or you may let the program find your files itself.

## Usage

* Clone or download wcompress
* Add below line to your .bashrc file for creating a path for wcompress
```
export PATH="/home/torvalds/Desktop/path_of/wcompress_folder:$PATH"
```
* Open a terminal where your web files exist
```
cd ~/Desktop/my_web_files
```
* Run wcompress
```
wcompress [html||css||js||all] [input||--all]
```
** Examples: **
* wcompress [html||css||js||all] [input||--all]
* wcompress html index.html -> Compresses a html file which named "index.html"
* wcompress css style.css -> Compresses a css file which named "style.css"
* wcompress js custom.js -> Compresses a css file which named "style.css"
* wcompress html --all -> Compresses all html files

## Is it safe?

No, it is still in development, please do not use wcompress for your projects.
wcompress creates a folder called "wcompress" and only modifies this folder and does not write your web files.

## Contributing

If you have any feature request, bug report, or patch feel free to contribute any time. This program is especially written in C because both it is fast and gives a chance for people who want to develop projects with C.