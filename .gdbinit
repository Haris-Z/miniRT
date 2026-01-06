#######################################
# global gdb setting
#######################################

# add path to gdbinit file for current project or globally
# (follow instructions from gdb) either add the next line to .configs/gdbinit file
# add-auto-load-safe-path ${HOME}/CC_miniRT/miniRT/miniRT/.gdbinit
# or         set auto-load safe-path /
# line to your configuration file "${HOME}/.config/gdb/gdbinit".

# to avoid yes/no 
# set confirm off

# full output shown no paging
set pagination on

# pretty printing
set print pretty on
set print array on
set print elements 0

#set verbose off
#set listsize 10

#######################################
# useful common commands
#######################################


#######################################
# custom commands
#######################################

# template/example
# define name_of_funcation
#   printf "\n--- name_of_function ---\n"
#   silent
#   # These will only print if they exist in the current frame
#   if $pc
#     printf "Function: %s\n", __func__
#   end
#   printf "  i          = "
#   if &i
#     print i
#   else
#     printf "(not in scope)\n"
#   end

#   printf "  some_variable_name  = "
#   if &some_variable_name
#     print some_variable_name
#   else
#     printf "(not in scope)\n"
#   end

#   printf "  some_variable_name2 = "
#   if &some_variable_name2
#     print some_variable_name2
#   else
#     printf "(not in scope)\n"
#   end

#   printf "  some_variable_name3          = "
#   if &some_variable_name3
#     print some_variable_name3
#   else
#     printf "(not in scope)\n"
#   end

#   printf "  some_variable_name4    = "
#   if &some_variable_name4
#     print some_variable_name4
#   else
#     printf "(not in scope)\n"
#   end
#   printf "--------------\n"
# end

# Show file descriptors visible to this process (Linux /proc)
define infofds
  printf "\n--- /proc/self/fd ---\n"
  shell ls -l /proc/self/fd
  printf "----------------------\n"
end

# set all the interesting breakpoints for program
define bprogramname
  printf "Setting programname-related breakpoints...\n"
  break main
  break somefunc1
  break somefunc2
  break somefunc3
  break somefunc4
  break somefunc5
  break somefunc6
  break somefunc7
end


