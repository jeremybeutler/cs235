//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <string>
#include <utility>
#include "SetInterface.h"
#include "HashMapInterface.h"

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

// Generic template for map<key,value>
template<typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
	private:
		size_t sizeMap;
		std::pair<K, V>** map;
	public:
		HashMap() : sizeMap(0)
		{
			map = new std::pair<K, V>*[DEFAULT_MAP_HASH_TABLE_SIZE];
			for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; ++i)
			{
				map[i] = NULL;
			}
		}
		~HashMap() { clear();  delete [] map; }

		/** Read/write index access operator.
		If the key is not found, an entry is made for it.
		@return: Read and write access to the value mapped to the provided key. */
		virtual V& operator[](const K& key)
		{
			size_t i = generateHashIndex(key);
			//if found, return value associated with the key
			size_t probes = 0;
			while (true)
			{
				size_t temp = (i + (probes * probes)) % max_size();
				if (found(key) && (map[temp]->first == key))
				{
					return map[temp]->second;
				}
				else if (map[temp] == NULL)
				{
					map[temp] = new std::pair<K, V>;
					map[temp]->first = key;
					sizeMap++;
					return map[temp]->second;
				}
				
				probes++;
			}
			
		}

		/** @return: the number of elements that match the key in the Map. */
		virtual size_t count(const K& key) 
		{
			size_t matches = 0;
			for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
			{
				if (map[i] != NULL && map[i]->first == key)
				{
					matches++;
				}
			}
			return matches;
		}

		/** Removes all items from the Map. */
		virtual void clear() 
		{
			for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
			{
				if (map[i] != NULL)
				{
					delete map[i];
					map[i] = NULL;
				}
			}
			sizeMap = 0;
		}

		/** @return: number of Key-Value pairs stored in the Map. */
		virtual size_t size() const
		{
			return sizeMap;
		}

		/** @return: maximum number of Key-Value pairs that the Map can hold. */
		virtual size_t max_size() const
		{
			return DEFAULT_MAP_HASH_TABLE_SIZE;
		}

		/** @return: string representation of Key-Value pairs in Map. */
		virtual std::string toString() const
		{
			std::stringstream out;
			out << size() << "/" << max_size() << std::endl;
			for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
			{
				if (map[i] != NULL)
				{
					out << "[" << i << ":" << map[i]->first << "->" << map[i]->second << "]" << std::endl;
				}
			}
			return out.str();
		}
	
		size_t generateHashIndex(std::string keyStr)
		{
			long long hash = 0;
			for (unsigned int i = 0; i < keyStr.length(); i++) 
			{
				char c = keyStr[i];
				hash += (long long)(c * pow(HASH_CONSTANT, keyStr.length() - i - 1));
			}
			//std::cout << hash % max_size() << std::endl;
			return hash % max_size();
		}

		bool found(const K& key)
		{
			return (count(key) > 0) ? true : false;
		}

};
#endif // HASH_MAP_H