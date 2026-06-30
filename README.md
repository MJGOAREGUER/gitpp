# What is it

My own git version working with Javascript

Structure des dossiers

mygit/
├── src/
│   ├── main.cpp
│   ├── repository/
│   │   ├── Repository.hpp / .cpp
│   │   └── Config.hpp / .cpp
│   ├── objects/
│   │   ├── GitObject.hpp        ← classe de base
│   │   ├── Blob.hpp / .cpp      ← fichier
│   │   ├── Tree.hpp / .cpp      ← dossier
│   │   ├── Commit.hpp / .cpp    ← commit
│   │   └── Tag.hpp / .cpp
│   ├── storage/
│   │   ├── ObjectStore.hpp / .cpp   ← lire/écrire les objets
│   │   └── Index.hpp / .cpp         ← staging area
│   ├── refs/
│   │   └── RefManager.hpp / .cpp    ← HEAD, branches
│   └── commands/
│       ├── Command.hpp          ← interface de base
│       ├── InitCommand.cpp
│       ├── AddCommand.cpp
│       ├── CommitCommand.cpp
│       ├── LogCommand.cpp
│       └── ...
├── CMakeLists.txt
└── README.md
