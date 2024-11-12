import redis
import random

# Connect to the Redis server
def connect_redis(host, port, db, password, username):
    try:
        return redis.Redis(host=host, port=port, db=db, password=password, username=username)
    except redis.RedisError as e:
        print(f"Error connecting to Redis: {e}")
        return None

# Store key-value pairs in Redis
def store_data(redis_connection, data):
    try:
        for key, value in data.items():
            redis_connection.set(key, value)
        print(f"Successfully stored {len(data)} key-value pairs.")
    except redis.RedisError as e:
        print(f"Error storing data: {e}")

# Randomly retrieve key-value pair from Redis
def retrieve_random_data(redis_connection, keys):
    if not keys:
        print("No keys provided for retrieval.")
        return
    random_key = random.choice(keys)
    try:
        value = redis_connection.get(random_key).decode("utf-8")
        print(f"The value of \"{random_key}\" is \"{value}\".")
    except redis.RedisError as e:
        print(f"Error retrieving data: {e}")

def main():
    # Connect to Redis
    r = connect_redis('localhost', 6379, 0, 'Anapurp43$$', 'vmadmin')
    if r is None:
        return

    # Define key-value pairs to store
    key_value_pairs = {
        'comedian': 'Dave Chapelle',
        'fallfromgrace': 'Will Smith',
        'cupof': 'Joe Mama',
        'hulu': 'The Bear',
        'gandhi': '"Be the change you want to see in the world"'
    }

    # Store data in Redis
    store_data(r, key_value_pairs)

    # Retrieve a random key-value pair
    retrieve_random_data(r, list(key_value_pairs.keys()))

if __name__ == "__main__":
    main()