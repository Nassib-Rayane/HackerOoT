set remote noack-packet on
define target hookpost-remote
    source tools/gdb_script.py
end