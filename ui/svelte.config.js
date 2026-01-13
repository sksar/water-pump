import adapter from '@sveltejs/adapter-static';

/** @type {import('@sveltejs/kit').Config} */
const config = {
    kit: {
        adapter: adapter({
            pages: '../fs',
            fallback: 'index.html'
        }),
        router: {
            type: 'hash'
        },
        output: {
            bundleStrategy: "inline",
        }
    }
};

export default config;
