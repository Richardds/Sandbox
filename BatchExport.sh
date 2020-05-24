#!/bin/bash

find Intermediate/Models/ -type f -exec basename "{}" .fbx \; | while read -d $'\n' NAME
do
    ./MeshExporter.sh "$NAME"
done
