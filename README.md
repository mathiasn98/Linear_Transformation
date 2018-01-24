# Linear_Transformation
Linear transformation using OpenGL API.
setelah melengkapi Mingw dengan freeglu library
maka untuk compilingnya cukup dengan command atau menekan f6:

NPP_SAVE
cd $(CURRENT_DIRECTORY)
g++ -std=gnu++14 "$(NAME_PART).cpp" -o "$(NAME_PART)" -lglu32 -lopengl32 -lfreeglut

lalu program akan segera selesai tercompile
