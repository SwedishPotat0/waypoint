# Waypoint

Waypoint is a CLI tool for fast file navigation through bookmarks, tags & groups in a terminal centric workflow.

Have you ever forgotten where a file in your project is located? Then Waypoint could be for you, instead of having to remember filepaths you can instead open your files through memorable names.

```bash
waypoint add main ~/Documents/project1/main.cpp
waypoint open main
```
This will add project1's main.cpp under the name main and then directly open it up by just using the name main.

## Why use waypoint?
So why use waypoint if you already use tools like fzf?
fzf is designed to fuzzy search across your filesystem, quickly helping you find files based on potential matches.
Waypoint takes another approach, it lets you assign memorable, persistant names to files and access them instantly by said names.

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

After first run you will find all default Waypoint files in `~/.waypoint`, you can modify these manually, but be sure to keep to the fileformating that Waypoint has automatically made, otherwise it could break things.

## How to use Waypoint

Waypoint has a selection of simple commands, these are:

* Add - Adds a filepath with a short name to your bookmarks
    
    Example:
    ``` bash
    waypoint add main ~/Documents/project1/main.cpp
    ```

* Open - Opens your files in a text editor

    Example:
    ```bash
    waypoint open main
    ```

* List - List bookmarks that match the given parameter **(Currently the only parameter: all)**

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
</details>

## Roadmap

- [ ] Implement All listed commands under planned commands

- [ ] Implement all planned parameters for list (tag, group, name)

- [x] Add waypoint config file

- [x] Create Vim plugin - See [waypoint.vim](https://github.com/SwedishPotat0/waypoint.vim)

- [ ] Add project specific waypoint files
