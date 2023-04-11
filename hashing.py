import hashlib

# generate an ETag for a resource
def generate_etag(resource):
    # calculate a hash value for the resource
    md5 = hashlib.md5()
    md5.update(resource.encode('utf-8'))
    hash_value = md5.digest()

    # convert the hash value to a string
    etag = '"' + ''.join('%02x' % byte for byte in hash_value) + '"'

    return etag

print(generate_etag('WWWW/index.html'))
