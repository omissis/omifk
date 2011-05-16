<?php

/* vim: set expandtab tabstop=2 shiftwidth=2 softtabstop=2: */

/**
 * Omifk modules library
 *
 * PHP version 5.2
 *
 * @category Frameworks
 * @package  Omifk
 * @author   Claudio Beatrice <claudi0.beatric3@gmail.com>
 * @license  http://www.php.net/license/3_01.txt  PHP License 3.01
 * @version  SVN: $Id$
 * @link     http://www.silent-voice.org/
 */

/**
 * Return the list of supported hooks
 *
 * @return array containing supported hooks
 */
function omifk_list_hooks() {
  return array(
    'init',
    'pre_exec',
    'main',
    'post_exec',
  );
}

/**
 * Loop on all the files in the Module directory, try to include and run them.
 *
 * @return void
 */
function omifk_main_loop() {
  global $omifk_config;
  // Open module directory
  $handle = opendir(OMIFK_DIRECTORY_MODULES);
  // If it exists and it is browsable
  if ($handle) {
    // Loop on every file and directory
    while (false !== ($module_filename = readdir($handle))) {
      // If the considered one doesn't start with '.' then include the module
      if (strpos($module_filename, '.') !== 0 && is_dir(OMIFK_DIRECTORY_MODULES . $module_filename)) {
        $module_name = str_replace('.module', '', $module_filename);
        akh_set_recursive($omifk_config, array('modules', $module_name), omifk_include_module($module_name));
      }
    }
    // Close directory handler
    closedir($handle);
  }
  // Run the hooks implemented in the active modules
  omifk_run_modules();
}

/**
 * Loops on all active modules' implemented hook and run them
 *
 * @global array $omifk_config
 *
 * @return void
 */
function omifk_run_modules() {
  global $omifk_config;

  $hooks   = omifk_list_hooks();
  $modules = akh_get($omifk_config, 'modules');

  foreach ($hooks as $hook) {
    foreach ($modules as $module => $active) {
      if (!$active) {
        continue;
      }
      omifk_run_hook($module, $hook);
    }
  }
}

/**
 * Include a module
 *
 * @param string $module_name string containing module name
 *
 * @return boolean true if module's been loaded succesfully
 */
function omifk_include_module($module_name) {
  global $omifk_config;

  $module_filename_prefix = OMIFK_DIRECTORY_MODULES . $module_name . '/' . $module_name;
  $module_filename        = $module_filename_prefix . '.module';
  $module_config_filename = $module_filename_prefix . '.info';

  $omifk_config = array_merge($omifk_config, array($module_name => parse_ini_file($module_config_filename, true)));

  return (boolean)(akh_get_recursive($omifk_config, array($module_name, 'active'), true)) ?
    (file_exists($module_filename) ? include_once $module_filename : false) :
    true;
}

/**
 * Run a hook implemented in the given module if exists
 *
 * @param $module_name string containing module's name
 *
 * @return null
 */
function omifk_run_hook($module_name, $hook_name = 'main') {
  $module_hook = $module_name . '_' . $hook_name;
  if (function_exists($module_hook)) {
    call_user_func($module_hook);
  }
}

/**
 * Check if a module exits and if it has a config file
 *
 * @param $module_name string containing module's name
 *
 * @return boolean
 */
function omifk_check_module($module_name) {
    $module_filename_prefix = OMIFK_DIRECTORY_MODULES . $module_name . '/' . $module_name;
    $module_filename        = $module_filename_prefix . '.module';
    $module_config_filename = $module_filename_prefix . '.info';

    if (!file_exists($module_filename)) {
      return false;
    }

    if (file_exists($module_config_filename)) {
      return false;
    }

    return true;
}

/**
 * Return the absolute path of a module
 *
 * @param string $module_name string containing module name
 *
 * @return string containing absolute module's path
 */
function omifk_get_module_path($module_name) {
   return OMIFK_DIRECTORY_MODULES . $module_name . '/';
}

/**
 * Return module configuration
 *
 * @param string $module_name string containing module name
 *
 * @return array containing module's configuration
 */
function omifk_read_module_config($module_name) {
    global $omifk_config;

    return akh_get($omifk_config, $module_name, array());
}