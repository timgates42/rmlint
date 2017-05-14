/**
* This file is part of rmlint.
*
*  rmlint is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  rmlint is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with rmlint.  If not, see <http://www.gnu.org/licenses/>.
*
* Authors:
*
*  - Christopher <sahib> Pahl 2010-2015 (https://github.com/sahib)
*  - Daniel <SeeSpotRun> T.   2014-2015 (https://github.com/SeeSpotRun)
*
* Hosted on http://github.com/sahib/rmlint
**/

#ifndef RM_SETTINGS_H
#define RM_SETTINGS_H

#include <stdio.h>

#include "checksum.h"
#include "pathtricia.h"
#include "utilities.h"

/* Struct for paths passed to rmlint from command line (or stdin) */
typedef struct RmPath {
    /* the RealPath of the passed string */
    char *path;

    /* index number (command line order) */
    guint idx;

    /* whether path was tagged as preferred path */
    bool is_prefd;

    /* whether to treat all files under path as one filesystem */
    bool treat_as_single_vol;
} RmPath;

/* Storage struct for all options settable in cmdline. */
typedef struct RmCfg {
    gboolean with_color;
    gboolean with_stdout_color;
    gboolean with_stderr_color;

    gboolean crossdev;
    gboolean ignore_hidden;
    gboolean partial_hidden;
    gboolean follow_symlinks;
    gboolean see_symlinks;
    gboolean find_badids;
    gboolean find_badlinks;
    gboolean find_duplicates;
    gboolean find_emptydirs;
    gboolean find_nonstripped;
    gboolean find_emptyfiles;
    gboolean keep_all_tagged;
    gboolean keep_all_untagged;
    gboolean must_match_tagged;
    gboolean must_match_untagged;
    gboolean find_hardlinked_dupes;
    gboolean limits_specified;
    gboolean filter_mtime;
    gboolean match_basename;
    gboolean unmatched_basenames;
    gboolean match_with_extension;
    gboolean match_without_extension;
    gboolean merge_directories;
    gboolean honour_dir_layout;
    gboolean write_cksum_to_xattr;
    gboolean read_cksum_from_xattr;
    gboolean clear_xattr_fields;
    gboolean write_unfinished;
    gboolean build_fiemap;
    gboolean use_buffered_read;
    gboolean fake_fiemap;
    gboolean progress_enabled;
    gboolean list_mounts;
    gboolean replay;

    int permissions;

    gdouble min_mtime;
    gdouble mtime_window;
    gint depth;
    gint verbosity;

    gdouble skip_start_factor;
    gdouble skip_end_factor;

    gboolean use_absolute_start_offset;
    gboolean use_absolute_end_offset;

    RmOff skip_start_offset;
    RmOff skip_end_offset;

    /* paths passed by command line */
    GSList *paths;
    GSList *json_paths;
    guint path_count;

    /* working dir rmlint called from */
    char *iwd;

    /* the full command line */
    char *joined_argv;

    char *sort_criteria;
    char rank_criteria[64];

    RmTrie file_trie;

    RmOff minsize;
    RmOff maxsize;
    RmOff threads;
    guint threads_per_disk;
    RmDigestType checksum_type;

    /* total number of bytes we are allowed to use (target only) */
    RmOff total_mem;

    /* number of bytes to read before going back to start of disk
     * (too big a sweep risks metadata getting pushed out of ram)*/
    RmOff sweep_size;
    RmOff sweep_count;

    gboolean shred_always_wait;
    gboolean shred_never_wait;
    gboolean fake_pathindex_as_disk;
    gboolean fake_abort;

    /* If true, files are hold back to
     * the end of the program run and printed then.
     */
    gboolean cache_file_structs;
} RmCfg;

/**
 * @brief Reset RmCfg to default cfg and all other vars to 0.
 */
void rm_cfg_set_default(RmCfg *cfg);

/**
 * @brief check and add a path to cfg->paths.
 */
guint rm_cfg_add_path(RmCfg *cfg, bool is_prefd, const char *path);

/**
 * @brief free all data associated with cfg->paths.
 */
void rm_cfg_free_paths(RmCfg *cfg);

#endif /* end of include guard */
