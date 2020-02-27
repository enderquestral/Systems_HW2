// cache_lib.cc
// Written by Hannah Hellerstein & Danny Riso

#include "cache.hh"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>

using namespace std;

/*
 * Notes from Eitan:
 *
 * You will implement your cache as a RAM-based storage of values, indexed by keys.
 * All keys and values will reside in main memory.
 * The cache needs to conform to the interface (API, or contract) that's provided in the attached cache.hh header file.
 * This API abstracts away the implementation of the cache while retaining a fixed interface.
 * You'll write a cache_lib.cc file that implements the interface, any way you see fit.
 * I recommend you start with the most trivial implementation you can think of---the quickest code you can write
 * that will compile and work all the functions---even if not terribly efficiently.
 */

//Need a hash table sooner or later
//Read through all the text of the assignment first

// Type definitions (if need defining beyond .hh's declaration):

// The link in cache.hh, https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/,
// is super important to know what Impl is and how to implement it here
struct Cache::Impl
{
	unordered_map<string, void*, hash_func> map;
	vector<key_type> holdkeys;
	index_type maximummemory;
	index_type usedmemory;
	Impl(index_type maxmem, evictor_type evictor, hash_func hasher) : map(1, hasher) { //set to 1 bucket?
		map.max_load_factor(0.8); //Init max load factor to something
		usedmemory = 0;
		maximummemory = maxmem;
		//Init with something here
	}
	void del(key_type key) {
		
	}

	void set(key_type key, val_type val, index_type size) {
		if (usedmemory + size <= maximummemory)
		{
			
		}
		map[key] = static_cast<const void*>(val);
		//map.insert((key,val))

	}

	val_type get(key_type key, index_type& val_size) const{
		
	}
	index_type space_used() const{
		return usedmemory;
	}
	void clear(){
		usedmemory = 0;
		map.clear();
		holdkeys.clear();
		maximummemory = 0;
	}
};

// Constructor & Destructor:

// Create a new cache object with a given maximum memory capacity.
//Indexer, function, function
Cache::Cache(index_type maxmem,
		evictor_type evictor = [](){ return 0; },
		hash_func hasher = std::hash<std::string>())
	: pImpl_(new Impl(maxmem, evictor, hasher)) {
	// Cache constructor
}

Cache::~Cache() = default; //Maybe not default if we need to do some memory management?
	// Cache destructor
	// Don't need to explicitly 'delete pImpl_' because it's a unique_ptr,
	// and it'll delete itself once it's out of scope


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
	pImpl_->set(key, val, size);
}

val_type Cache::get(key_type key, index_type& val_size) const {
	// The 'const' modifier means that no member variable of the Cache we're calling 'get' on can be modified
	
	// Return a pointer to the value associated with the key in the cache; if not found, return null
	// Set the actual size of the returned value (in bytes) in val_size
	pImpl->get(key, val_size);
}

void Cache::del(key_type key) {
	// If an object w/ key 'key' is in the cache, remove it
	pImpl->del(key);
}

index_type Cache::space_used() const {
	// Compute the total amount of memory used by all the current cache values (keys not included)
	return pImpl->space_used();
}
