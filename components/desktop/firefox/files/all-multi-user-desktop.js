// Disable "safe browsing" feature that hogs CPU, HDD, etc.
pref("browser.safebrowsing.enabled", false);
pref("browser.safebrowsing.malware.enabled", false);

//  Limit the "location-bar suggestions"
pref("browser.urlbar.maxRichResults", 3);

// Disable offline/disk caching of web pages
pref("browser.cache.offline.enable", false);
pref("browser.cache.disk.enable", false);

// Change the default cache:
pref("browser.cache.memory.enable",true);
pref("browser.cache.memory.capacity", 1024);
