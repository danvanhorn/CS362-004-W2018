import org.junit.Assert;

import junit.framework.TestCase;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

	public UrlValidatorTest(String testName) {
		super(testName);
	}

	public void testManualTest() {
		String[] schemes = {"http","https"};
		UrlValidator urlValidator = new UrlValidator(schemes);
		boolean result1 = urlValidator.isValid("https://google.com");
		boolean result2 = urlValidator.isValid("http://google.com/");
		boolean result3 = urlValidator.isValid("http://twitter.com/posts/?items=400");
		boolean result4 = urlValidator.isValid("file://sample.xml");

		System.out.println("https://www.google.com " + urlValidator.isValid("https://www.google.com"));
		System.out.println("http://google.com/ " + urlValidator.isValid("http://google.com/"));
		System.out.println("http://twitter.com/posts/?items=400 " + urlValidator.isValid("http://twitter.com/posts/?items=400"));
		System.out.println("file://sample.xml " + urlValidator.isValid("file://sample.xml"));

		Assert.assertTrue(result1);
		Assert.assertTrue(result2);
		Assert.assertTrue(result3);
		Assert.assertTrue(result4);
	}

	// vary the scheme, authority, and port and run the rest
	public void testYourFirstPartition() {
		int idx = 0;
		UrlValidator urlValidator = new UrlValidator();
		StringBuilder url = new StringBuilder();
		for(int i = 0; i < 6; i++) {
			for(Object part: partition1) {
				ResultPair[] result = (ResultPair[]) part;
				url.append(result[idx].item);
			}
			System.out.println(url + " " + urlValidator.isValid(url.toString()));
			Assert.assertTrue(urlValidator.isValid(url.toString()));
			idx++;
		}	
	}

	// vary the url path
	public void testYourSecondPartition() {
		int idx = 0;
		UrlValidator urlValidator = new UrlValidator();
		for(int i = 0; i < 6; i++) {
			StringBuilder url = new StringBuilder();
			url.append("http://google.com");
			for(Object part: partition1) {
				ResultPair[] result = (ResultPair[]) part;
				url.append(result[idx].item);
			}
			System.out.println(url + " " + urlValidator.isValid(url.toString()));
			Assert.assertTrue(urlValidator.isValid(url.toString()));
			idx++;
		}	
	}

	public void testIsValid() {
		UrlValidator urlValidator = new UrlValidator();
		//test null value
		assertTrue(!urlValidator.isValid(null));
		//test not null value
		assertTrue(urlValidator.isValid("https://www.google.com"));

		
		//test something with invalid structure
		assertTrue(!urlValidator.isValid(".comwww.googlehttps://"));
		//test something with valid structure
		assertTrue(urlValidator.isValid("https://www.google.com"));

		//test something with invalid authority
		assertTrue(urlValidator.isValid("https://.1.2.3.4"));
		//test something with valid authority
		assertTrue(urlValidator.isValid("https://www.google.com"));
		//test something with valid authority
		assertTrue(urlValidator.isValid("https://255.255.255.255"));
		//test something with valid ipv6 authority
		assertTrue(urlValidator.isValid("https://fe80::d415:104c:41f1:fda1%15"));
		
		
		//test something with invalid path
		assertTrue(urlValidator.isValid("https://www.google.com/..//file"));

		//test something with valid path
		assertTrue(urlValidator.isValid("https://www.google.com/test1"));

		//test something with invalid query
		assertTrue(urlValidator.isValid("https://www.google.com/test1?//"));

		//test something with valid query
		assertTrue(urlValidator.isValid("https://www.google.com/test1?action=view"));

	}
	
	
ResultPair[] testUrlScheme = {
				new ResultPair("http://", true),
               new ResultPair("ftp://", true),
               new ResultPair("h3t://", true),
               new ResultPair("3ht://", false),
               new ResultPair("http:/", false),
               new ResultPair("http:", false)
              };

ResultPair[] testUrlAuthority = {
		  new ResultPair("www.google.com", true),
          new ResultPair("go.com", true),
          new ResultPair("255.255.255.255", true),
          new ResultPair("256.256.256.256", false),
          new ResultPair("255.com", true),
          new ResultPair(".1.2.3.4", false)
};
ResultPair[] testUrlPort = {
		new ResultPair(":80", true),
             new ResultPair(":65535", true),
             new ResultPair(":0", true),
             new ResultPair("", true),
             new ResultPair(":-1", false),
            new ResultPair(":65636",false)
};
ResultPair[] testPath = {
		new ResultPair("/test1", true),
          new ResultPair("/t123", true),
          new ResultPair("/$23", true),
          new ResultPair("/..", false),
          new ResultPair("/../", false),
          new ResultPair("/..//file", false)
};

ResultPair[] testUrlQuery = {
		new ResultPair("?action=view", true),
        new ResultPair("?action=edit&mode=up", true),
        new ResultPair("?//", false),
		new ResultPair("?action=view", true),
        new ResultPair("?action=edit&mode=up", true),
        new ResultPair("", true)
};

Object[] partition1 = {testUrlScheme, testUrlAuthority, testUrlPort};
Object[] partition2 = {testPath, testUrlQuery};

}
