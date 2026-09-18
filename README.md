# Waypoint

Waypoint is a CLI tool for fast file navigation through bookmarks, tags & groups in a terminal centric workflow.

Have you ever forgotten where a file in your project is located? Then Waypoint could be for you, instead of having to remember file-paths you can instead open your files through memorable names.

![](https://github.com/SwedishPotat0/waypoint/blob/main/waypoint.gif)

## Why use waypoint?
So why use waypoint if you already use tools like fzf?
fzf is designed to fuzzy search across your filesystem, quickly helping you find files based on potential matches.
Waypoint takes another approach, it lets you assign memorable, persistent names to files and access them instantly by said names.

## How to install

**Support on Windows and Mac is currently untested.**

Requirements: g++
<details>
<summary>Manual Install</summary>

To install Waypoint on unix you need to clone the repo, compile it and then place it in `/usr/local/bin` to make it globally callable.

```bash
git clone https://github.com/SwedishPotat0/waypoint
cd waypoint
g++ *.cpp -o waypoint
sudo mv waypoint /usr/local/bin/waypoint
```

And now you should be able to call `waypoint` in your terminal.
</details>

<details>
<summary>Automatic Install</summary>

You can do a automated install of waypoint by running the `install.sh`

```bash
git clone https://github.com/SwedishPotat0/waypoint
cd waypoint
bash install.sh
```
</details>

After installing waypoint try to run `waypoint` in your terminal to allow it to generate necessary files.

After first run you will find all default Waypoint files in `~/.waypoint`, you can modify these manually, but be sure to keep to the file-formatting that Waypoint has automatically made, otherwise it could break things.

## How to configure waypoint

A config file for waypoint exsists in ~/.waypoint/config.txt

Currently the only option to configure is what editor waypoint should open your files in, by default the editr will be set to vim.    

## Local waypoints

There are two "types" of waypoints, local and global, global waypoints can be used nearly anywhere on your system, while local waypoints can only be accsesd in the directory where it exsists.

To creat local waypoints you begin whit runing the `init` command to initilise a local waypoint directory, then you navigate these waypoints like the global ones.

## How to use Waypoint

Waypoint has a selection of simple commands, these are:

* Add - Adds a file-path with a short name to your bookmarks
    
    Example:
    ``` bash
    waypoint add main ~/Documents/project1/main.cpp
    ```

* Open - Opens your files in a text editor

    Example:
    ```bash
    waypoint open main
    ```

* List - List bookmarks that match the given parameter 

    Example:
    ```bash
    waypoint list all 
    ```

    Output:
    ```bash
    main ~/Documents/project1/main.cpp
    ```

* Tag - Tags a bookmark with the given tag

    Example:
    ```bash
    waypoint tag main important
    ```

* Remove - Removes the targeted bookmark from waypoint 

    Example:
    ```bash
    waypoint remove main
    ```

* Init - Makes a local waypoint directory in your current directory allowing the use of local waypoints
    
    Example:
    ```bash
    waypoint init
    ```

<details>
<summary>Planned Commands</summary>

* Group - Group together files that for example belong to the same project 

    Example:
    ```bash
    waypoint group main project1
    ```

* Jump - Jump to the location of the bookmark in your filesystem 

    Example:
    ```bash
    waypoint jump main
    ```

* Rename - Rename a waypoint

    Example:
    ```bash
    waypoint rename oldname newname
    ```

* Untag - Removes one or all tags from a waypoint

    Example:
    ```bash
    waypoint untag main
    ```
    Removes all tags from main
        
     Example:
    ```bash
    waypoint untag main important
    ```
    Removes the tag important from main

</details>

## Roadmap

- [ ] Implement All listed commands under planned commands

- [ ] Implement all planned parameters for list

    - [x] Name

    - [x] Tag

    - [ ] Group

- [ ] Make list function for names/tags/groups that contain the filter term and not just a exact match

- [x] Add waypoint config file

- [x] Create Vim plugin - See [waypoint.vim](https://github.com/SwedishPotat0/waypoint.vim)

- [x] Add project specific waypoint files
