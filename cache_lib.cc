#include "cache.hh"

//Read through all the text of the assignment first

// Since we're given cache.hh, a lot of Part 1 is just implementing whatever methods we need
// from there to in order to get something compilable and theoretically like a cache.


// Type definitions (if need defining beyond .hh's declaration):

// The link in cache.hh, https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/,
// is super important to know what Impl is and how to implement it here
struct Impl {
	
}

// Constructor & Destructor:

Cache::Cache(index_type maxmem,
		evictor_type evictor = [](){ return 0; },
		hash_func hasher = std::hash<std::string>())
	: pImpl_(new Impl) {
	// Cache constructor
}

Cache::~Cache() {
	// Cache destructor
	// Don't need to explicitly 'delete pImpl_' because it's a unique_ptr,
	// and it'll delete itself once it's out of scope
}

// Methods:

void Cache::set(key_type key, val_type val, index_type size) {
	// Description taken from .hh file:
	//
	// Add a <key, value> pair to the cache.
	// If the key is already in the cache, its value gets overwritten by this new one
	// !!! Both the key and the value must be deep-copied, not just pointer-copied
	// If maxmem capacity is exceeded, sufficient (?) values will be removed
	// from the cache to accommodate the new value.
		// "Sufficient" just meaning "satisfying some definition we assign", I think
	
}

val_type Cache::get(key_type key, index_type& val_size) const {
	// The 'const' modifier means that no member variable of the Cache we're calling 'get' on can be modified
	
	// Return a pointer to the value associated with the key in the cache; if not found, return null
	// Set the actual size of the returned value (in bytes) in val_size
}

void Cache::del(key_type key) {
	// If an object w/ key 'key' is in the cache, remove it
}

index_type Cache::space_used() const {
	// Compute the total amount of memory used by all the current cache values (keys not included)
}
