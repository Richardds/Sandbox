#!/bin/bash

MESH_EXPORTER='./Bin/Debug/MeshExporter.exe'
MODEL="$1"

$MESH_EXPORTER Intermediate/Models/${MODEL}.fbx Resources/Models/${MODEL}.model

