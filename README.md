# appel-gmod-x86
32-bit C++ Garry's Mod hack fork

![script_tab](https://github.com/user-attachments/assets/606d8220-48ab-4c2c-8818-92991da12ce7)

## About project
Back in 2019~ish I was pretty active in Garry's Mod Russian SandBox server community, writing scripts for my own server, later being hired as a coder. 

It has always bugged me, that anyone who's server you can join, could simply destroy your data folder, lock you out of your game, snoop around your lan using DHTML *(including rebooting your router if you had default login credentials!)*. 

I liked visiting different sandbox servers, but I disagreed with that. The easiest mitigation to that would be blocking `SendLua()` and `net.Recieve()`, so that's what I did, and this project contains such options.
I also had a lot of fun coding and using different options from a "Script" tab, such as "Auto Heal" and "Physgun Tricks". 

This is a fork of FreeTheSkids by 1Lee, with much love, trial and error put into it. A lot more options have been added, but as this project was a part of my learning process, the codebase is **BAD and messy**, I wouldn't recommend using it for anything but as an example of how to implement some stuff.

## Features
<details>
<summary>Aimbot Tab</summary>

![aimbot_tab](https://github.com/user-attachments/assets/21754b18-5b24-4642-a69b-1f1beb577e5e)
</details>
<details>
<summary>HvH Tab</summary>

 ![hvh_tab](https://github.com/user-attachments/assets/13eb60a7-8593-4768-bf76-6c35164fafaf)
</details>
<details>
<summary>Visuals Tab</summary>

![vis_tab](https://github.com/user-attachments/assets/e74613de-c2fc-408a-af55-90da0b9d3354)

**Fullbright:**
![fullbright_vis](https://github.com/user-attachments/assets/3f0c8828-93d5-4a0c-804e-ccb636e517f9)

**Rainbow map:**
![rainbow_vis](https://github.com/user-attachments/assets/f96fee42-c04b-4537-a6b4-bd4c8a9ec6fe)

**FreeCam:**
![freecam_vis](https://github.com/user-attachments/assets/824a398b-21fd-4e33-9015-148b8ba79b09)

</details>
<details>
<summary>Players Tab</summary>

 ![player_tab](https://github.com/user-attachments/assets/9cabde79-34b6-4c7c-b968-eae40ede7368)
</details>
<details>
<summary>Script Tab</summary>
 
  ![script_tab](https://github.com/user-attachments/assets/f1ae227c-6405-483a-b2d0-7c815f231525)
</details>
<details>
<summary>Settings Tab</summary>
 
  ![settings_tab](https://github.com/user-attachments/assets/a65cf572-80e5-41eb-9e3c-6cd13d59f34d)
</details>

**Honorable Mentions:**
<details>
<summary>ImGui Lua Editor</summary>
  
![lua_editor](https://github.com/user-attachments/assets/ea29990d-4d73-4eed-80d6-f9c0d3b0e04e)

**Note**:
- Doesn't support inputting cyrillic symbols. Copy-paste works fine.
</details>

<details>
<summary>Auto Heal</summary>
 
[o.webm](https://github.com/user-attachments/assets/08e21a85-6070-47ec-a7a1-f2b6d17c1385)
</details>
<details>
<summary>Physgun Tricks</summary>
 
[o1.webm](https://github.com/user-attachments/assets/1186e461-9961-41d6-a4ff-7546c9c82858)
</details>
<details>
<summary>Lua Related</summary>
 
 **`SendLua()` detection and blocking:**
 
 ![sendlua1](https://github.com/user-attachments/assets/7e15a99c-d6e2-4a75-b2f2-f67e1a298b47)

**Client Lua dumper:**

![dumper](https://github.com/user-attachments/assets/924b3d8c-65de-44aa-a99c-ce68e9cd7711)
</details>

## Compatibility
This project is compatible with Garry's Mod 32-bit from 12th July 2021. 

You can downgrade to this version using steamcmd and `download_depot` command.

Proper commands with depot ids and manifests:

**Content:**
```
download_depot 4000 4001 8687231342132392405
```
**Binaries (32-bit):**
```
download_depot 4000 4002 4508641684765344429
```
## Compiling
This project compiles under Microsoft Visual Studio 2017.

**Requirements:**
- MS Detours Version 3.0 Build_343
- DX9SDK
- Patching 7617-th line in WinBase.h file related to Unicode.

This project hasn't been updated since 14 August 2021.

## Projects used
This is a fork of [FreeTheSkids](https://github.com/11Lee1/Free-The-Skids)

UI powered by [Dear Imgui](https://github.com/ocornut/imgui)

Lua editor powered by [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)



  
